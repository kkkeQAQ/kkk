#ifndef KMUTEX_H
#define KMUTEX_H

#include "KObject.h"
#include "pthread.h"

class KMutex : public KObject{
	pthread_mutex_t mutex;
public:
	KMutex(KObject *parent=nullptr):KObject(parent){};
};

#endif //KMUTEX_H
