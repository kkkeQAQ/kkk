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
#include "KMutex.h"

KMutex::KMutex(KObject *parent):KObject(parent)
{
	pthread_mutex_init(&mutex,NULL);
	bLock=false;
}

KMutex::~KMutex()
{
	pthread_mutex_destroy(&mutex);
}

bool KMutex::isLocked()
{
	return bLock;
}

int KMutex::lock()
{
	int res=pthread_mutex_lock(&mutex);
	bLock=true;
	return res;
}

int KMutex::unlock()
{
	bLock=false;
	return pthread_mutex_unlock(&mutex);
}

