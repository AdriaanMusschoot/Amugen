#include "SceneManager.h"
#include "Scene.h"
void amu::SceneManager::Update()
{
	for(auto& scene : m_ScenesUPtrVec)
	{
		scene->Update();
	}
}

void amu::SceneManager::Render()
{
	for (const auto& scene : m_ScenesUPtrVec)
	{
		scene->Render();
	}
}

void amu::SceneManager::CreateScene(const std::string& name, const std::function<void(Scene*)>& loadScene)
{
	std::unique_ptr sceneUPtr = std::make_unique<Scene>(name);
	loadScene(sceneUPtr.get());
	m_ScenesUPtrVec.emplace_back(std::move(sceneUPtr));
}
