#ifndef KMUTEX_H
#define KMUTEX_H

#include "KObject.h"
#include "pthread.h"

class KMutex : public KObject{
	pthread_mutex_t mutex;
	bool bLock;
public:
	KMutex(KObject *parent=nullptr);
	bool isLocked();
	int lock();
	int unlock();
};

#endif //KMUTEX_H
