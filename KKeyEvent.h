#ifndef KKEVENT_H
#define KKEVENT_H

#include "KEvent.h"

class KKeyEvent : public KEvent{
public:
	unsigned int key;
	KKeyEvent(unsigned int key=0):key(key)
	{
	}
};

#endif //KKEVENT_H
