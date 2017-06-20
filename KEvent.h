#ifndef KEVENT_H
#define KEVENT_H

#include "KObject.h"

class KEvent : public KObject {
public:
	KEvent(KObject *parent=nullptr);
};

#endif //KEVENT_H
