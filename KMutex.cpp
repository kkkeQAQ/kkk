#include "KMutex.h"

KMutex::KMutex(KObject *parent):KObject(parent)
{
	pthread_mutex_init(&mutex,NULL);
	bLock=false;
}

bool KMutex::isLocked()
{
	return bLock;
}

int KMutex::lock()
{
	pthread_mutex_lock(&mutex);
}

int KMutex::unlock()
{
	pthread_mutex_unlock(&mutex);
}
