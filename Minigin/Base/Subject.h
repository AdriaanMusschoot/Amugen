#pragma once
#include "Observer.h"
#include <vector>
#include "GameObject.h"
namespace amu
{

	class Subject
	{
	public:
		Subject(GameObject* ownerObjectPtr)
			: m_OwnerObjectPtr{ ownerObjectPtr }
		{}
		virtual ~Subject() = default;

		Subject(const Subject& other) = delete;
		Subject(Subject&& other) = delete;
		Subject& operator=(const Subject& other) = delete;
		Subject& operator=(Subject&& other) = delete;

		void AddObserver(Observer* observerToAddPtr)
		{
			m_ObserverPtrVec.emplace_back(observerToAddPtr);
		}

		void RemoveObserver(Observer* observerToRemovePtr)
		{
			std::erase_if(m_ObserverPtrVec,
				[&](const Observer* observerPtr)
				{
					return observerPtr == observerToRemovePtr;
				});
		}

		void NotifyObservers(Observer::EventType eventType)
		{
			for (const auto& observer : m_ObserverPtrVec)
			{
				observer->Notify(eventType, this);
			}
		}

		void NotifyDestruction()
		{
			for (const auto& observer : m_ObserverPtrVec)
			{
				observer->NotifyDestruction();
			}
		}
		GameObject* GetSubjectOwner() { return  m_OwnerObjectPtr; }
	private:
		GameObject* m_OwnerObjectPtr;
		std::vector<Observer*> m_ObserverPtrVec{};
	};

}