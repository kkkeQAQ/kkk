#include "KKeyListener.h"
#include "curses.h"
#include "KKeyEvent.h"
#include "KApplication.h"

KKeyListenner::KKeyListenner(KObject *parent):KThread(parent)
{
}

void KKeyListenner::run()
{
	while(true)
	{
		kApp->postEvent(nullptr,new KKeyEvent(getch()));
	}
}

