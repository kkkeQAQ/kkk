#ifndef KMUTEX_H
#define KMUTEX_H

#include "pthread.h"
#include "KObject.h"

class KMutex : public KObject{
private:
	pthread_mutex_t mutex;
	bool bLock;
public:
	KMutex(KObject *parent=nullptr);
	~KMutex()override;
	bool isLocked();
	int lock();
	int unlock();
};

#endif //KMUTEX_H
