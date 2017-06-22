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
#include "KSemaphore.h"

KSemaphore::KSemaphore(unsigned int num,KObject *parent):KObject(parent),num(num)
{
	pthread_cond_init(&cond,nullptr);
	pthread_mutex_init(&mutex,nullptr);
}

KSemaphore::~KSemaphore()
{
	pthread_cond_destroy(&cond);
	pthread_mutex_destroy(&mutex);
}

int KSemaphore::require(unsigned int num)
{
	pthread_mutex_lock(&mutex);
	while(num>this->num)
		pthread_cond_wait(&cond,&mutex);
	this->num-=num;
	pthread_mutex_unlock(&mutex);
}

int KSemaphore::release(unsigned int num)
{
	pthread_mutex_lock(&mutex);
	this->num+=num;
	pthread_cond_broadcast(&cond);
	pthread_mutex_unlock(&mutex);
}

