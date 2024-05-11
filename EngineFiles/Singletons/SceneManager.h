#ifndef AMU_SCENE_MANAGER_H
#define AMU_SCENE_MANAGER_H

#include <vector>
#include <string>
#include <memory>
#include "Singleton.h"
#include "Scene.h"
#include <functional>

namespace pacman
{

	class SceneManager final : public Singleton<SceneManager>
	{
	public:
		void CreateScene(std::string_view const& name, std::function<void(Scene*)> const& loadScene);

		void Update();
		void Render();
	private:
		friend class Singleton<SceneManager>;
		SceneManager() = default;
		std::vector<std::unique_ptr<Scene>> m_ScenesUPtrVec{};
	};

}

#endif //AMU_SCENE_MANAGER_H