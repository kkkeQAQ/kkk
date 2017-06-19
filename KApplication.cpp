#include "KApplication.h"
#include "curses.h"

KApplication::KApplication(int argc,char **argv):args(argv,argv+argc)
{
	self=this;
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
