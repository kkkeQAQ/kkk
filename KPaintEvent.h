#ifndef KPAINTEVENT_H
#define KPAINTEVENT_H

#include "KEvent.h"

class KPaintEvent : public KEvent {
public:
	KPaintEvent(KObject *parent=nullptr):KObject(parent){};
};

#endif //KPAINTEVENT_H
