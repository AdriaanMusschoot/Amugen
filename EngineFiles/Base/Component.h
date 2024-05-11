#ifndef AMU_COMPONENT_H
#define AMU_COMPONENT_H
#include <memory>

namespace amu
{

	class GameObject;

	class Component
	{
	public:
		explicit Component(GameObject * ownerObjectPtr)
			: m_OwnerGameObjectPtr{ ownerObjectPtr }
			, m_ToBeDestroyed{ false }
		{
		}
		virtual ~Component() = default;
	
		Component(const Component& other) = delete;
		Component(Component&& other) = delete;
		Component& operator=(const Component& other) = delete;
		Component& operator=(Component&& other) = delete;
	
	protected:
	
		virtual void Update() {}
		virtual void Render() const {}

		GameObject* GetComponentOwner() const { return m_OwnerGameObjectPtr; }

		void EnableToBeDestroyed() { m_ToBeDestroyed = true; }
		bool GetToBeDestroyed() const { return m_ToBeDestroyed; }
	private:
		friend class GameObject;

		GameObject* m_OwnerGameObjectPtr = nullptr;

		bool m_ToBeDestroyed = false;
	};

}

#endif //AMU_COMPONENT_H