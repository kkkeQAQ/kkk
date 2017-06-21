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
#include "KWidget.h"
#include "KPainter.h"

using namespace std;

int i=0;

class MainWindow : public KWidget {
private:
	KKeyListenner *keyListenner;
	int x=0,y=0;
protected:
	void paintEvent(KPaintEvent *)override
	{
		KPainter painter(this);
		painter.mvAddCh(x,y,'O');
	}
	void keyEvent(KKeyEvent *e)override
	{
		switch(e->key)
		{
		case 'q':
			kApp->quit();
			break;
		case KEY_UP:
			x--;
			break;
		case KEY_DOWN:
			x++;
			break;
		case KEY_LEFT:
			y--;
			break;
		case KEY_RIGHT:
			y++;
			break;
		}
		repaint();
	}
public:
	MainWindow(KObject *parent=nullptr):KWidget(0,0,0,0,parent==nullptr?kApp:parent)
	{
		keyListenner =new KKeyListenner(this);
		keyListenner->start();
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

