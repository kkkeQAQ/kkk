#include "KSemaphore.h"

KSemaphore::KSemaphore(unsigned int num,KObject *parent):KObject(parent),num(num)
{
	pthread_cond_init(&cond,nullptr);
	pthread_mutex_init(&mutex,nullptr);
}

KSemaphore::~KSemaphore()
{
	pthread_cond_destroy(&cond);
	pthread_mutex_destroy(&mutex);
}

int KSemaphore::require(unsigned int num)
{
	pthread_mutex_lock(&mutex);
	while(num>this->num)
		pthread_cond_wait(&cond,&mutex);
	this->num-=num;
	pthread_mutex_unlock(&mutex);
}

int KSemaphore::release(unsigned int num)
{
	pthread_mutex_lock(&mutex);
	this->num+=num;
	pthread_cond_broadcast(&cond);
	pthread_mutex_unlock(&mutex);
}

