#ifndef KTHREAD_H
#define KTHREAD_H

#include "KObject.h"
#include <pthread.h>
#include "KMutex.h"

class KThread : public KObject{
private:
	pthread_t tid=-1;
	long exitValue;
	static void startThread(KThread *const thread);
	KMutex mutex;
public:
	~KThread();
	KThread(KObject *parent=nullptr):KObject(parent){};
	static int join(KThread *const thread);
	int join();
	int cancel();
	int quit();
	virtual void run()=0;
	int start();
	bool isRunning()const;
	pthread_t getTid()const;
	long getExitValue()const;
};

#endif //KTHREAD_H
