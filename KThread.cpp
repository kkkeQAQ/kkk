#include "KThread.h"
#include <pthread.h>
#include <cassert>

void KThread::startThread(KThread *const thread)
{
	thread->run();
}

void KThread::start()
{
	assert(pthread_create(&tid,NULL,(void*(*)(void*))startThread,(void *)this)==0);
}

pthread_t KThread::getTid()const
{
	return tid;
}
