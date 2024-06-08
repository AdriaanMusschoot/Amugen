#include "Scene.h"
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

amu::GameObject* amu::Scene::Add(std::unique_ptr<GameObject> object)
{
	m_ToBeAddedUPtrVec.emplace_back(std::move(object));
	return m_ToBeAddedUPtrVec[std::ssize(m_ToBeAddedUPtrVec) - 1].get();
}

void amu::Scene::Remove()
{
	std::erase_if(m_GameObjectUPtrVec,
		[&](const std::unique_ptr<GameObject>& objectUPtr)
		{
			return objectUPtr->GetToBeDestroyed();
		});
}

void amu::Scene::AddPending()
{
	for (auto& toBeAddedUPtr : m_ToBeAddedUPtrVec)
	{
		m_GameObjectUPtrVec.emplace_back(std::move(toBeAddedUPtr));
	}
	m_ToBeAddedUPtrVec.clear();
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
					auto* distanceComponentPtr = objectOuter->GetComponent<DistanceComponent>();
					auto& posOuter = objectOuter->GetComponent<TransformComponent>()->GetWorldPosition();
					auto& posInner = objectInner->GetComponent<TransformComponent>()->GetWorldPosition();

					bool overlapping = distanceComponentPtr->Check(posOuter, posInner, 5);

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
	AddPending();
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
	return foundObjPtrVec;
}

