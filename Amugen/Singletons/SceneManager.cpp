#include "Singletons/SceneManager.h"
#include "Base/Scene.h"
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

amu::Scene& amu::SceneManager::CreateScene(const std::string& name, const std::function<void(Scene*)>& loadScene)
{
	std::unique_ptr sceneUPtr = std::make_unique<Scene>(name);
	loadScene(sceneUPtr.get());
	m_ScenesUPtrVec.emplace_back(std::move(sceneUPtr));
	return *m_ScenesUPtrVec[m_ScenesUPtrVec.size() - 1];
}
