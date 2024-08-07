#ifndef AMU_SCENE_MANAGER_H
#define AMU_SCENE_MANAGER_H

#include <vector>
#include <string>
#include <memory>
#include "Singleton.h"
#include "Scene.h"
#include <functional>

namespace amu
{

	class SceneManager final : public Singleton<SceneManager>
	{
	public:
		virtual ~SceneManager() = default;

		SceneManager(SceneManager const&) = delete;
		SceneManager(SceneManager&&) = delete;
		SceneManager& operator=(SceneManager const&) = delete;
		SceneManager& operator=(SceneManager&&) = delete;


		void CreateScene(std::string_view const& name, std::function<void(Scene*)> const& loadScene);

		void SetCurrentScene(std::string_view const& name);

		void Collision();

		void Update();
		void Render();

		Scene* GetSceneByName(std::string_view const& name) const;
	private:
		friend class Singleton<SceneManager>;
		explicit SceneManager() = default;
		std::vector<std::unique_ptr<Scene>> m_ScenesUPtrVec{};

		Scene* m_CurrentScenePtr{ nullptr };
	};

}

#endif //AMU_SCENE_MANAGER_H