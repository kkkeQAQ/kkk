#include "KThread.h"
#include <pthread.h>
#include <cstdio>
#include <stdlib.h>
#include <signal.h>

KThread::~KThread()
{
	if(tid!=pthread_t(-1))
	{
		pthread_kill(tid,SIGQUIT);
	}
}

int KThread::join(KThread *const thread)
{
	return pthread_join(thread->getTid(),(void**)&thread->exitValue);
}

void KThread::startThread(KThread *const thread)
{
	thread->run();
	thread->tid=-1;
}

int KThread::start()
{
	if(tid!=pthread_t(-1))return -1;
	return pthread_create(&tid,NULL,(void*(*)(void*))startThread,(void *)this);
}

pthread_t KThread::getTid()const
{
	return tid;
}

long KThread::getExitValue()const
{
	return exitValue;
}

