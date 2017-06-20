#ifndef KEVENT_H
#define KEVENT_H

#include "KObject.h"

class KEvent : public KObject {
public:
	KEvent(KObject *parent=nullptr):KObject(parent){};
};

#endif //KEVENT_H
