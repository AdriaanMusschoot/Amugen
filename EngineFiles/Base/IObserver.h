#ifndef AMU_IOBSERVER_H
#define AMU_IOBSERVER_H
namespace amu
{
	class Subject;

	class IObserver
	{
	public:
		virtual ~IObserver() = default;

		using Event = int;
		virtual void Notify(Event eventType, Subject* subjectPtr) const = 0;
		virtual void NotifyDestruction() = 0;
	private:

	};

}

#endif //AMU_IOBSERVER_H