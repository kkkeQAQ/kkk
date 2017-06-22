/**
 * Copyright (C) 2017 kkkeQAQ <kkke@nwsuaf.edu.cn>.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 **/
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
