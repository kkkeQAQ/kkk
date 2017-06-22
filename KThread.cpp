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

