#ifndef AMU_SCENE_MANAGER_H
#define AMU_SCENE_MANAGER_H

#include <vector>
#include <string>
#include <memory>
#include "Singleton.h"
#include "Base/Scene.h"
#include <functional>

namespace amu
{

	class SceneManager final : public Singleton<SceneManager>
	{
	public:
		Scene& CreateScene(const std::string& name, const std::function<void(Scene*)>& loadScene);

		void Update();
		void Render();
	private:
		friend class Singleton<SceneManager>;
		SceneManager() = default;
		std::vector<std::unique_ptr<Scene>> m_ScenesUPtrVec{};
	};

}

#endif