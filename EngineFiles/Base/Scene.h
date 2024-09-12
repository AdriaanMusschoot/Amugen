#ifndef AMU_SCENE_H
#define AMU_SCENE_H
#include <vector>
#include <memory>
#include <string>

#include "GameObject.h"

namespace amu
{

	class Scene final
	{
	public:
		explicit Scene(std::string_view const& name);
		~Scene();

		Scene(Scene const&) = delete;
		Scene(Scene&&) = delete;
		Scene& operator=(Scene const&) = delete;
		Scene& operator=(Scene&&) = delete;

		GameObject* Add(std::unique_ptr<GameObject> object);
		void RemoveAll();

		void Collision();
		void Update();
		void Render() const;

		std::string_view GetTag();

		std::vector<GameObject*> GetObjectsOfType(std::string_view const& type);
	private:
		//when storing data need string otherwise if string_view goes out of scope data becomes invalid
		std::string const m_Name = "";
		std::vector<std::unique_ptr<GameObject>> m_GameObjectUPtrVec{};
		std::vector<std::unique_ptr<amu::GameObject>> m_ToBeAddedUPtrVec{};

		void Remove();
		void AddPending();
	};

}

#endif //AMU_SCENE_H