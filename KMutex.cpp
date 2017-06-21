#include "KMutex.h"

KMutex::KMutex(KObject *parent):KObject(parent)
{
	pthread_mutex_init(&mutex,NULL);
	bLock=false;
}

KMutex::~KMutex()
{
	pthread_mutex_destroy(&mutex);
}

bool KMutex::isLocked()
{
	return bLock;
}

int KMutex::lock()
{
	int res=pthread_mutex_lock(&mutex);
	bLock=true;
	return res;
}

int KMutex::unlock()
{
	bLock=false;
	return pthread_mutex_unlock(&mutex);
}

