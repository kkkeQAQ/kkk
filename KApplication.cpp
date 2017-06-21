#include "KApplication.h"
#include "KQuitEvent.h"
#include "KPaintEvent.h"
#include <curses.h>

KApplication* KApplication::self=nullptr;

KApplication::KApplication(int argc,char **argv):args(argv,argv+argc)
{
	self=this;
	eventLoop=new KEventLoop(this);
	initscr();
	noecho();
	cbreak();
	keypad(stdscr,true);
}

KApplication::~KApplication()
{
	endwin();
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

