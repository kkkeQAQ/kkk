#ifndef KEVENTLOOP_H
#define KEVENTLOOP_H

#include "KObject.h"
#include "KMutex.h"
#include "KEvent.h"
#include <queue>

class KEventLoop : public KObject{
private:
	std::queue<std::pair<KObject*,KEvent*>> q;
	KMutex mutex;
	static void processEvent(KObject *parent,KObject *object,KEvent *event);
public:
	KEventLoop(KObject *parent=nullptr);
	void postEvent(KObject* object,KEvent* event);
	void processEvent();
	int exec();
};

#endif //KEVENTLOOP_H
