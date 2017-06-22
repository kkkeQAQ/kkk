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
#include "KApplication.h"
#include "KQuitEvent.h"
#include "KPaintEvent.h"
#include <curses.h>
#include <iostream>
#include <locale.h>

KApplication* KApplication::self=nullptr;

KApplication::KApplication(int argc,char **argv):args(argv,argv+argc)
{
	setlocale(LC_ALL,"");
	self=this;
	eventLoop=new KEventLoop(this);
	std::cout<<"\e[?25l";
	initscr();
	noecho();
	cbreak();
	start_color();
	keypad(stdscr,true);
}

KApplication::~KApplication()
{
	endwin();
	std::cout<<"\e[?25h";
}

std::vector<char*>& KApplication::arguments()
{
	return args;
}

KApplication* KApplication::instance()
{
	return self;
}

void KApplication::postEvent(KObject *object,KEvent *event)
{
	self->eventLoop->postEvent(object,event);
}

int KApplication::exec()
{
	postEvent(nullptr,new KPaintEvent());
	return eventLoop->exec();
}

void KApplication::exit(int exitCode)
{
	eventLoop->postEvent(nullptr,new KQuitEvent(exitCode));
}

void KApplication::quit()
{
	exit(0);
}

