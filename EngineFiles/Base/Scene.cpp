#include "Scene.h"
#include <string>
#include "CollisionComponent.h"
#include <execution>
#include <iterator>
#include <algorithm>

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
	for (auto& objectOuter : m_GameObjectUPtrVec)
	{
		if (objectOuter->GetCollider() == nullptr)
		{
			continue;
		}
		for (auto& objectInner : m_GameObjectUPtrVec)
		{
			if (objectInner == objectOuter)
			{
				continue;
			}
			if (objectInner->GetCollider() == nullptr)
			{
				continue;
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

