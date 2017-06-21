#include "KThread.h"
#include <pthread.h>
#include <cstdio>
#include <stdlib.h>
#include <signal.h>

KThread::~KThread()
{
	cancel();
}

int KThread::join(KThread *const thread)
{
	return thread->join();
}

bool KThread::isRunning()const
{
	return tid != pthread_t(-1);
}

int KThread::join()
{
	int res=-1;
	mutex.lock();
	if(isRunning())res=pthread_join(tid,(void**)&exitValue);
	mutex.unlock();
	return res;
}

int KThread::cancel()
{
	int res=-1;
	mutex.lock();
	if(isRunning())res=pthread_cancel(tid);
	mutex.unlock();
	return res;
}

void KThread::startThread(KThread *const thread)
{
	thread->run();
	thread->mutex.lock();
	thread->tid=-1;
	thread->mutex.unlock();
}

int KThread::start()
{
	int res=-1;
	mutex.lock();
	if(!isRunning())res=pthread_create(&tid,NULL,(void*(*)(void*))startThread,(void *)this);
	mutex.unlock();
	return res;
}

pthread_t KThread::getTid()const
{
	return tid;
}

long KThread::getExitValue()const
{
	return exitValue;
}

