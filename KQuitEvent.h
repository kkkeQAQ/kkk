#ifndef KQUITEVENT_H
#define KQUITEVENT_H

#include "KEvent.h"

class KQuitEvent : public KEvent {
public:
	EventType type()override
	{
		return QuitEvent;
	}
};

#endif //KQUITEVENT_H
