#include "Scene.h"
#include <string>
#include "CollisionComponent.h"
#include <execution>
#include <iterator>
#include <algorithm>
#include <iostream>
unsigned int amu::Scene::m_IdCounter = 0;

amu::Scene::Scene(std::string_view const& name) 
	: m_Name{ name }
{
}

amu::Scene::~Scene() = default;

void amu::Scene::Add(std::unique_ptr<GameObject> object)
{
	m_GameObjectUPtrVec.emplace_back(std::move(object));
}

void amu::Scene::Remove()
{
	std::erase_if(m_GameObjectUPtrVec,
		[&](const std::unique_ptr<GameObject>& objectUPtr)
		{
			return objectUPtr->GetToBeDestroyed();
		});
}

void amu::Scene::RemoveAll()
{
	m_GameObjectUPtrVec.clear();
}

void amu::Scene::Collision()
{
	for (int idxOuter{}; idxOuter < std::ssize(m_GameObjectUPtrVec); ++idxOuter)
	{
		auto& objectOuter = m_GameObjectUPtrVec[idxOuter];

		if (auto* outerCollider{ objectOuter->GetCollider() }; outerCollider != nullptr)
		{
			if (outerCollider->NumberOfTags() == 0)
			{
				continue;
			}

			for (int idxInner{ idxOuter }; idxInner < std::ssize(m_GameObjectUPtrVec); ++idxInner)
			{
				auto& objectInner = m_GameObjectUPtrVec[idxInner];

				if (objectOuter == objectInner)
				{
					continue;
				}

				if (auto* innerCollider{ objectInner->GetCollider() }; innerCollider != nullptr)
				{
					bool overlapping = objectOuter->GetComponent<DistanceComponent>()->Check(objectOuter->GetComponent<TransformComponent>()->GetWorldPosition(), objectInner->GetComponent<TransformComponent>()->GetWorldPosition(), 5);

					if (overlapping)
					{
						outerCollider->OnCollision(innerCollider);
						innerCollider->OnCollision(outerCollider);
					}
				}
			}
		}
	}
}

void amu::Scene::Update()
{
	for(auto& object : m_GameObjectUPtrVec)
	{
		object->Update();
	}
	Remove();
}

void amu::Scene::Render() const
{
	for (auto const& object : m_GameObjectUPtrVec)
	{
		object->Render();
	}
}

std::vector<amu::GameObject*> amu::Scene::GetObjectsOfType(std::string_view const& type)
{
	std::vector<GameObject*> foundObjPtrVec{};
	for (auto const& objPtr : m_GameObjectUPtrVec)
	{
		if (objPtr->GetTag() == type)
		{
			foundObjPtrVec.emplace_back(objPtr.get());
		}
	}
	//std::copy_if(m_GameObjectUPtrVec.begin(), m_GameObjectUPtrVec.end(),
	//	std::back_inserter(foundObjects),
	//	[&](std::unique_ptr<GameObject> objPtr) 
	//	{
	//		return objPtr->GetTag() == type;
	//	});
	return foundObjPtrVec;
}

