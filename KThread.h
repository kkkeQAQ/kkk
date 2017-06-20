#ifndef KTHREAD_H
#define KTHREAD_H

#include "KObject.h"
#include <pthread.h>

class KThread : public KObject{
private:
	pthread_t tid=-1;
	long exitValue;
	static void startThread(KThread *const thread);
public:
	~KThread();
	KThread(KObject *parent=nullptr):KObject(parent){};
	static int join(KThread *const thread);
	int quit();
	virtual void run()=0;
	int start();
	pthread_t getTid()const;
	long getExitValue()const;
};

#endif //KTHREAD_H
