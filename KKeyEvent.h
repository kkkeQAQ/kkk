#ifndef KKEVENT_H
#define KKEVENT_H

#include "KEvent.h"

class KKeyEvent : public KEvent{
public:
	unsigned int key;
	KKeyEvent(unsigned int key=0):key(key)
	{
	}
	EventType type()override
	{
		return KeyEvent;
	}
};

#endif //KKEVENT_H
