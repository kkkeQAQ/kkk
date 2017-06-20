#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include "KThread.h"
#include <unistd.h>
#include "KApplication.h"
#include "KQuitEvent.h"
#include <curses.h>

using namespace std;

class Thread:public KThread{
public:
	void run()override
	{
		static int i=0;
		while(true)
		{
			i++;
			if(i>=10)
			{
				kApp->postEvent(nullptr,new KQuitEvent());
				return;
			}
			mvaddstr(i,0,to_string(i).c_str());
			refresh();
			usleep(500000);
		}
	}
};

int main(int argc,char **argv)
{
	KApplication a(argc,argv);
	Thread t;
	t.start();
	//	Thread::join(&t);
	cout<<t.getTid();
	a.exec();
	Thread::join(&t);cout<<111<<endl;
	mvaddstr(LINES/2,COLS/2,"quit");
	return a.exec();
}

