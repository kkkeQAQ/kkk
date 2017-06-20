#ifndef KEVENTLOOP_H
#define KEVENTLOOP_H

#include "KMutex.h"
#include "KEvent.h"
#include <queue>

class KEventLoop : public KMutex{
private:
	queue<KEvent*> q;
public:
	KEventLoop(KObject *parent=nullptr);
	void processEvent();
	void exec();
};

#endif //KEVENTLOOP_H
