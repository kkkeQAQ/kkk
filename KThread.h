#ifndef KTHREAD_H
#define KTHREAD_H

#include <pthread.h>

class KThread {
private:
	pthread_t tid=-1;
	static void start(KThread *const thread);
public:
	virtual void run();
	void start();
	pthread_t getTid()const;
};

#endif //KTHREAD_H
