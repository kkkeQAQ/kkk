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
	}
public:
	HelpWindow(int x,int y,int height,int weight,KWidget *parent) : KWidget(x,y,height,weight,parent)
	{
		int h=help.size();
		int w=0;
		for(auto &i:help)w=max(w,(int)i.length());
		setWindow(x,y,h,w);
	}
	
};

class MainWindow : public KWidget,public KThread {
private:
	KKeyListenner *keyListenner;
	double x=0,y=0,vx=0,vy=0;
	int l,r;
protected:
	void paintEvent(KPaintEvent *)override
	{
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
			if(KWidget::isAvailable())hide();
			else show();
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

