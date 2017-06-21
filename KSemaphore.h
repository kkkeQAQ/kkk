#ifndef KSEMPHORE_H
#define KSEMPHORE_H

#include "KObject.h"
#include "pthread.h"

class KSemaphore : public KObject{
private:
	pthread_mutex_t mutex;
	pthread_cond_t cond;
	unsigned int num;
public:
	KSemaphore(unsigned int num=1,KObject *parent=nullptr);
	~KSemaphore()override;
	int require(unsigned int num=1);
	int release(unsigned int num=1);
};

#endif //KSEMPHORE_H
