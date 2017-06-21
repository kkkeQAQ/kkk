#ifndef KMUTEX_H
#define KMUTEX_H

#include "pthread.h"

class KMutex{
private:
	pthread_mutex_t mutex;
	bool bLock;
public:
	KMutex();
	bool isLocked();
	int lock();
	int unlock();
};

#endif //KMUTEX_H
