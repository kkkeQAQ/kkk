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
public:
	MainWindow(KObject *parent=nullptr):KObject(parent)
	{
		(new KKeyListenner(kApp))->start();
	}
	void event(KEvent *event)override
	{
		if(event->type()==KEvent::KeyEvent)
		{
			KKeyEvent *keyEvent=static_cast<KKeyEvent*>(event);
			cout<<keyEvent->key<<endl;
			if(isalpha(keyEvent->key)||isdigit(keyEvent->key))
			{
				addch(keyEvent->key);
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

