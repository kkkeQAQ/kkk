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
#ifndef KAPPLICATION_H
#define KAPPLICATION_H

#include "KObject.h"
#include <vector>
#include "KEvent.h"
#include "KEventLoop.h"

class KApplication:public KObject{
private:
	std::vector<char*>args;
	static KApplication *self;
	KEventLoop *eventLoop;
public:
	static KApplication* instance();
	static void postEvent(KObject *object,KEvent *event);
	KApplication(int argc,char **argv);
	~KApplication()override;
	std::vector<char*>& arguments();
	void quit();
	void exit(int exitCode);
	int exec();
};

#define kApp KApplication::instance()

#endif //KAPPLICATION_H
