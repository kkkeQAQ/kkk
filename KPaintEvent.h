#ifndef KPAINTEVENT_H
#define KPAINTEVENT_H

#include "KEvent.h"

class KPaintEvent : public KEvent {
public:
	EventType type()override
	{
		return PaintEvent;
	}
};

#endif //KPAINTEVENT_H
