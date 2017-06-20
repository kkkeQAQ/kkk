#ifndef KEVENTLOOP_H
#define KEVENTLOOP_H

#include "KMutex.h"
#include "KEvent.h"
#include <queue>

class KEventLoop : public KMutex{
private:
	std::queue<std::pair<KObject*,KEvent*>> q;
	void processEvent(KObject *parent,KObject *object,KEvent *event);
public:
	KEventLoop(KObject *parent=nullptr);
	void postEvent(KObject* object,KEvent* event);
	void processEvent();
	int exec();
};

#endif //KEVENTLOOP_H
