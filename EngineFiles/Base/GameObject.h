#ifndef AMU_GAME_OBJECT_H
#define AMU_GAME_OBJECT_H
#include <memory>
#include <vector>
#include "Component.h"

namespace amu
{
	class GameObject final
	{
	public:
		GameObject()
			: m_ToBeDestroyed{ false }
			, m_ParentObjectPtr{ nullptr }
		{
		}

		~GameObject() = default;
		GameObject(GameObject const&) = delete;
		GameObject(GameObject&&) = delete;
		GameObject& operator=(GameObject const&) = delete;
		GameObject& operator=(GameObject&&) = delete;

		void Update();
		void Render() const;

		template <typename T, typename... Args>
		void AddComponent(Args&&... args)
		{
			if (not ComponentAdded<T>())
			{
				m_ComponentUPtrVec.emplace_back(std::make_unique<T>(std::forward<Args>(args)...));
			}
		}

		template <typename T>
		void RemoveComponent()
		{
			//erase removes element from start iterator (given by remove_if) to end iterator
			m_ComponentUPtrVec.erase
			(
				//moves element to be removed to the back 
				std::remove_if(m_ComponentUPtrVec.begin(), m_ComponentUPtrVec.end(),
					[](const auto& component)
					{
						return dynamic_cast<T*>(component.get()) != nullptr;
					}),
				m_ComponentUPtrVec.end()
			);
		}

		template <typename T> 
		T* GetComponent() const
		{
			for (const auto& component : m_ComponentUPtrVec)
			{
				if (const auto & neededComponent = dynamic_cast<T*>(component.get()); neededComponent != nullptr)
				{
					return neededComponent;
				}
			}
			return nullptr;
		}

		template <typename T>
		bool ComponentAdded() const
		{
			for (const auto& component : m_ComponentUPtrVec)
			{
				if (const auto neededComponent = dynamic_cast<T*>(component.get()); neededComponent != nullptr)
				{
					return true;
				}
			}
			return false;
		}

		void EnableToBeDestroyed();
		bool GetToBeDestroyed() const;

		GameObject* GetParent() const;
		void SetParent(GameObject* newParentObjectPtr, bool keepWorldPosition);
		std::int64_t GetChildCount() const;
		GameObject* GetChildAt(std::int64_t idx) const;
	private:
		std::vector<std::unique_ptr<Component>> m_ComponentUPtrVec{};

		bool m_ToBeDestroyed = false;

		//raw ptrs because transform logic, don't need to destroy
		GameObject* m_ParentObjectPtr = nullptr;
		std::vector<GameObject*> m_ChildObjectPtrVec{};

		bool IsChild(GameObject const* parentObjectPtr) const;
		void RemoveChild(GameObject* gameObjectPtr);
		void AddChild(GameObject* gameObjectPtr);
	};
	
}

#endif //AMU_GAME_OBJECT_H