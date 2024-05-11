#include "Scene.h"
#include <string>

using namespace amu;

unsigned int Scene::m_IdCounter = 0;

Scene::Scene(std::string_view const& name) 
	: m_Name{ name }
{
}

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
	for (auto const& object : m_GameObjectUPtrVec)
	{
		object->Render();
	}
}

