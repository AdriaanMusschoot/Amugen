#ifndef AMU_SUBJECT_H
#define AMU_SUBJECT_H

#include "IObserver.h"
#include <vector>
#include "GameObject.h"

namespace amu
{

	class Subject
	{
	public:
		explicit Subject(GameObject* ownerObjectPtr)
			: m_OwnerObjectPtr{ ownerObjectPtr }
		{}
		virtual ~Subject() = default;

		Subject(Subject const&) = delete;
		Subject(Subject&&) = delete;
		Subject& operator=(Subject const&) = delete;
		Subject& operator=(Subject&&) = delete;

		void AddObserver(IObserver* observerToAddPtr)
		{
			m_ObserverPtrVec.emplace_back(observerToAddPtr);
		}

		void RemoveObserver(IObserver* observerToRemovePtr)
		{
			std::erase_if(m_ObserverPtrVec,
				[&](const IObserver* observerPtr)
				{
					return observerPtr == observerToRemovePtr;
				});
		}

		void NotifyObservers(IObserver::Event eventType)
		{
			for (IObserver* const observer : m_ObserverPtrVec)
			{
				observer->OnNotify(eventType, this);
			}
		}

		void NotifyDestruction()
		{
			for (IObserver* const observer : m_ObserverPtrVec)
			{
				observer->NotifyDestruction();
			}
		}
		GameObject* GetSubjectOwner() { return  m_OwnerObjectPtr; }
	private:
		GameObject* m_OwnerObjectPtr;
		std::vector<IObserver*> m_ObserverPtrVec{};
	};

}

#endif //AMU_SUBJECT_H