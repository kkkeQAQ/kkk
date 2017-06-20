#ifndef KKEVENT_H
#define KKEVENT_H

#include "KEvent.h"

class KKeyEvent : public KEvent{
public:
	unsigned int key;
};

#endif //KKEVENT_H
