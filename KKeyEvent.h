#ifndef KKEVENT_H
#define KKEVENT_H

#include "KEvent.h"

class KKeyEvent : public KEvent{
public:
	KKeyEvent(KObject *parent=nullptr):KObject(parent){};
	unsigned int key;
};

#endif //KKEVENT_H
