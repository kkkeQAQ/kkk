#include "KThread.h"

void KThread::start(KThread *const thread)
{
	thread->run();
}

void KThread::start()
{
	pthread_create(&tid,NULL,(void *)startThread,(void *)this);
}

pthread_t KThread::getTid()const
{
	return tid;
}
