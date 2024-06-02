#ifndef AMU_COLLIDER_IOBSERVER_H
#define AMU_COLLIDER_IOBSERVER_H

#include "GameObject.h"

namespace amu
{

	class IColliderObserver
	{

		public:
			virtual ~IColliderObserver() = default;

			using Event = int;
			virtual void OnNotify(Event eventType, amu::Component * colliderPtr1, amu::Component* colliderPtr2) const = 0;
			virtual void OnNotifyDestruction() = 0;
		private:

	};

}

#endif