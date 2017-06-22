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
#ifndef KEVENTLOOP_H
#define KEVENTLOOP_H

#include "KObject.h"
#include "KMutex.h"
#include "KEvent.h"
#include "KSemaphore.h"
#include <queue>

class KEventLoop : public KObject{
private:
	std::queue<std::pair<KObject*,KEvent*>> q;
	KMutex mutex;
	KSemaphore semaphore;
	static void processEvent(KObject *parent,KObject *object,KEvent *event);
public:
	KEventLoop(KObject *parent=nullptr);
	void postEvent(KObject* object,KEvent* event);
	void processEvent();
	int exec();
};

#endif //KEVENTLOOP_H
