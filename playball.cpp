#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include "KThread.h"
#include <unistd.h>
#include "KApplication.h"
#include "KQuitEvent.h"
#include "KKeyListener.h"
#include <curses.h>
#include "KKeyEvent.h"

using namespace std;

int i=0;

class MainWindow : public KObject {
	KKeyListenner *keyListenner;
public:
	MainWindow(KObject *parent=nullptr):KObject(parent==nullptr?kApp:parent)
	{
		keyListenner =new KKeyListenner(this);
		keyListenner->start();
	}
	void event(KEvent *event)override
	{
		if(event->type()==KEvent::KeyEvent)
		{
			KKeyEvent *keyEvent=static_cast<KKeyEvent*>(event);
			if(isalpha(keyEvent->key)||isdigit(keyEvent->key))
			{
				addch(1+keyEvent->key);
				refresh();
				if(keyEvent->key=='q')kApp->postEvent(nullptr,new KQuitEvent());
			}
		}
	}
	void show()
	{
	}
};

int main(int argc,char **argv)
{
	KApplication a(argc,argv);
	MainWindow w(&a);
	w.show();
	return a.exec();
}

