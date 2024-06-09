#include "SceneManager.h"
#include "SceneManager.h"
#include "SceneManager.h"
#include "Scene.h"
void amu::SceneManager::Update()
{
	m_CurrentScenePtr->Update();
}

void amu::SceneManager::Render()
{
	m_CurrentScenePtr->Render();
}

amu::Scene* amu::SceneManager::GetSceneByName(std::string_view const& name) const
{
	return (*std::find_if(m_ScenesUPtrVec.begin(), m_ScenesUPtrVec.end(), [&](auto const& scene) { return name == scene->GetTag(); })).get();
}

void amu::SceneManager::CreateScene(std::string_view const& name, std::function<void(Scene*)> const& loadScene)
{
	std::unique_ptr sceneUPtr = std::make_unique<Scene>(name);
	loadScene(sceneUPtr.get());
	m_ScenesUPtrVec.emplace_back(std::move(sceneUPtr));
}

void amu::SceneManager::SetCurrentScene(std::string_view const& name)
{
	m_CurrentScenePtr = GetSceneByName(name);
}

void amu::SceneManager::Collision()
{
	m_CurrentScenePtr->Collision();
}
