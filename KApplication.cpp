#include "KApplication.h"
#include "curses.h"

KApplication* KApplication::self=nullptr;

KApplication::KApplication(int argc,char **argv):args(argv,argv+argc)
{
	self=this;
	eventLoop=new KEventLoop(this);
	initscr();
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
	eventLoop->exec();
}

