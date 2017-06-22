#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <unistd.h>
#include <vector>

#include "KThread.h"
#include "KApplication.h"
#include "KKeyListener.h"
#include "KKeyEvent.h"
#include "KWidget.h"
#include "KPainter.h"
#include "KFont.h"

using namespace std;

int i=0;

class HelpWindow : public KWidget {
private:
	vector<string>help={
		"           Welcome to the game",
		"",
		"Help:",
		" 'N': Start a new game.",
		" 'q': Quit game.",
		" 'f': Accelerate the ball in X direction",
		" 's': Slow down the ball in X direction",
		" 'F': Accelerate the ball in Y direction",
		" 'S': Slow down the ball in Y direction",
	};
protected:
	void paintEvent(KPaintEvent *)override
	{
		KPainter painter(this);
		painter.box();
		for(int i=0;i<(int)help.size();i++)
		{
			painter.mvAddStr(i+1,1,help[i].c_str());
		}
	}
public:
	HelpWindow(KWidget *parent) : KWidget(0,0,0,0,parent)
	{
		int h=help.size();
		int w=0;
		for(auto &i:help)w=max(w,(int)i.length());
		setWindow(0,0,h+2,w+2);
	}
	
};

class MainWindow : public KWidget,public KThread {
private:
	KKeyListenner *keyListenner;
	HelpWindow *helpWindow;
	double x=0,y=0,vx=0,vy=0;
	int l,r;
protected:
	void paintEvent(KPaintEvent *)override
	{
		int h=helpWindow->getHeight();
		int w=helpWindow->getWeight();
		helpWindow->setWindow(getHeight()/2-h/2,getWeight()/2-w/2,h,w);
		char s[]="O";
		KPainter painter(this);
		KFont font(KFont::RED,KFont::YELLOW);
		painter.setFont(&font);
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
			if(!helpWindow->isAvailable())
				helpWindow->show();
			else
				helpWindow->hide();
		}
	}
public:
	MainWindow(KWidget *parent=nullptr):KWidget(0,0,0,0,parent)
	{
		x=getHeight()/2;
		y=getWeight()/2;
		keyListenner =new KKeyListenner(static_cast<KWidget*>(this));
		keyListenner->start();
		start();
		helpWindow=new HelpWindow(this);
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
			usleep(50000);
		}
	}

};

int main(int argc,char **argv)
{
	KApplication a(argc,argv);
	MainWindow w;
	w.show();
	return a.exec();
}

