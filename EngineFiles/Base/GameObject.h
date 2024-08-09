#ifndef AMU_GAME_OBJECT_H
#define AMU_GAME_OBJECT_H
#include <memory>
#include <vector>
#include "CollisionComponent.h"
#include <string>

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
		T* AddComponent(Args&&... args)
		{
			if (not ComponentAdded<T>())
			{
				m_ComponentUPtrVec.emplace_back(std::make_unique<T>(std::forward<Args>(args)...));
				return dynamic_cast<T*>(m_ComponentUPtrVec[std::ssize(m_ComponentUPtrVec) - 1].get());
			}
			return nullptr;
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

		void AddCollider(std::unique_ptr<amu::CollisionComponent> collisionComponentUPtr)
		{
			m_CollisionComponentUPtr = std::move(collisionComponentUPtr);
		}

		amu::CollisionComponent* GetCollider() const
		{
			return m_CollisionComponentUPtr.get();
		}

		void EnableToBeDestroyed();
		bool GetToBeDestroyed() const;

		GameObject* GetParent() const;
		void SetParent(GameObject* newParentObjectPtr, bool keepWorldPosition);
		size_t GetChildCount() const;
		GameObject* GetChildAt(unsigned int idx) const;

		void SetTag(std::string_view const& tag);
		std::string_view GetTag() const;
	private:
		std::vector<std::unique_ptr<Component>> m_ComponentUPtrVec{};
		std::string m_Tag{ "empty" };
		bool m_ToBeDestroyed = false;

		//raw ptrs because transform logic, don't need to destroy
		GameObject* m_ParentObjectPtr = nullptr;
		std::vector<GameObject*> m_ChildObjectPtrVec{};

		std::unique_ptr<amu::CollisionComponent> m_CollisionComponentUPtr{ nullptr };

		bool IsChild(GameObject const* parentObjectPtr) const;
		void RemoveChild(GameObject* gameObjectPtr);
		void AddChild(GameObject* gameObjectPtr);
	};
	
}

#endif //AMU_GAME_OBJECT_H