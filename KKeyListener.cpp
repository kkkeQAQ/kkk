#include "KKeyListener.h"
#include "curses.h"
#include "KKeyEvent.h"
#include "KApplication.h"

KKeyListenner::KKeyListenner(KObject *parent):KThread(parent)
{
}

KKeyListenner::~KKeyListenner()
{
	flag=false;
	join(this);
}

void KKeyListenner::run()
{
	while(flag)
	{
		kApp->postEvent(nullptr,new KKeyEvent(getch()));
	}
}

