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
	pthread_cancel(this->getTid());
	join(this);
}

void KKeyListenner::run()
{
	while(flag)
	{
		kApp->postEvent(parent(),new KKeyEvent(getch()));
	}
}

