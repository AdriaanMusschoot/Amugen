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
		virtual void OnNotify(Event eventType, Subject* subjectPtr) = 0;
		virtual void NotifyDestruction() {};
	private:

	};

}

#endif //AMU_IOBSERVER_H