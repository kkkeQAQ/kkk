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
