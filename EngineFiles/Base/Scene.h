#ifndef AMU_SCENE_H
#define AMU_SCENE_H
#include "GameObject.h"
#include <vector>
#include <memory>
#include <string>

namespace amu
{
	class Scene final
	{
	public:
		explicit Scene(std::string_view const& name);
		~Scene();

		Scene(Scene const& other) = delete;
		Scene(Scene&& other) = delete;
		Scene& operator=(Scene const& other) = delete;
		Scene& operator=(Scene&& other) = delete;

		void Add(std::unique_ptr<GameObject> object);
		void RemoveAll();

		void Update();
		void Render() const;

	private:
		//when storing data need string otherwise if string_view goes out of scope data becomes invalid
		std::string const m_Name = "";
		std::vector<std::unique_ptr<GameObject>> m_GameObjectUPtrVec{};

		static unsigned int m_IdCounter; 
		void Remove();
	};

}

#endif //AMU_SCENE_H