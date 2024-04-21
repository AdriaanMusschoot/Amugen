#include "Base/Scene.h"
#include <string>

using namespace amu;

unsigned int Scene::m_idCounter = 0;

Scene::Scene(const std::string& name) : m_name(name) {}

Scene::~Scene() = default;

void Scene::Add(std::unique_ptr<GameObject> object)
{
	m_GameObjectUPtrVec.emplace_back(std::move(object));
}

void Scene::Remove()
{
	std::erase_if(m_GameObjectUPtrVec,
		[&](const std::unique_ptr<GameObject>& objectUPtr)
		{
			return objectUPtr->GetToBeDestroyed();
		});
}

void Scene::RemoveAll()
{
	m_GameObjectUPtrVec.clear();
}

void Scene::Update()
{
	for(auto& object : m_GameObjectUPtrVec)
	{
		object->Update();
	}
	Remove();
}

void Scene::Render() const
{
	for (const auto& object : m_GameObjectUPtrVec)
	{
		object->Render();
	}
}

