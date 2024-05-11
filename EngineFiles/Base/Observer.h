#pragma once

namespace pacman
{
	class Subject;

	class Observer
	{
	public:
		enum class EventType
		{
			PacmanDied,
			PacmanEat,
		};

		virtual ~Observer() = default;
		virtual void Notify(EventType eventType, Subject* subjectPtr) = 0;
		virtual void NotifyDestruction() = 0;
	private:

	};

}