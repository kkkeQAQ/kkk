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
#include <cmath>

using namespace std;

int i=0;

class MainWindow : public KWidget,public KThread {
private:
	KKeyListenner *keyListenner;
	double x=0,y=0,vx=0,vy=0;
protected:
	void paintEvent(KPaintEvent *)override
	{
		char s[]="O";
		KPainter painter(this);
		painter.attrOn(A_DIM);
		painter.mvAddStr(x,y,s);
	}
	void keyEvent(KKeyEvent *e)override
	{
		switch(e->key)
		{
		case 'q':
			kApp->quit();
			break;
		case KEY_UP:
			vx--;
			break;
		case KEY_DOWN:
			vx++;
			break;
		case KEY_LEFT:
			vy--;
			break;
		case KEY_RIGHT:
			vy++;
			break;
		case 'h':
			if(KWidget::isAvailable())hide();
			else show();
		}
	}
public:
	MainWindow(KObject *parent=nullptr):KWidget(0,0,0,0,parent==nullptr?kApp:parent)
	{
		x=getHeight()/2;
		y=getWeight()/2;
		keyListenner =new KKeyListenner(static_cast<KWidget*>(this));
		keyListenner->start();
		start();
	}

	~MainWindow()override
	{
		KThread::cancel();
		KThread::join();
	}

	void run()override
	{
		while(true)
		{
			x+=vx/2;
			if(x<0)
			{
				x=0;
				vx=abs(vx);
			}
			else if(x>=getHeight())
			{
				x=getHeight()-1;
				vx=-abs(vx);
			}
			y+=vy;
			if(y<0)
			{
				y=0;
				vy=abs(vy);
			}
			else if(y>=getWeight())
			{
				y=getWeight()-1;
				vy=-abs(vy);
			}
			repaint();
			usleep(30000);
		}
	}

};

int main(int argc,char **argv)
{
	KApplication a(argc,argv);
	MainWindow w(&a);
	w.show();
	return a.exec();
}

