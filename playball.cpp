#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <unistd.h>
#include <vector>
#include <ctime>
#include <stdlib.h>

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
	double x=0,y=0,vx=0,vy=0,addv=1;
	int l=0,ll=20,lv=4;
	int score=0;
protected:
	void paintEvent(KPaintEvent *)override
	{
		int h=helpWindow->getHeight();
		int w=helpWindow->getWeight();
		helpWindow->setWindow(getHeight()/2-h/2,getWeight()/2-w/2,h,w);
		KPainter painter(this);
		KFont fBall(KFont::RED,KFont::RED);
		KFont fPlayer(KFont::BLUE,KFont::BLUE);
		painter.setFont(&fBall);
		painter.mvAddStr(x,y,"  ");
		painter.setFont(&fPlayer);
		for(int i=0;i<ll;i++)painter.mvAddCh(getHeight()-1,l+i,' ');

		string he="help: h ?";
		painter.setFont(&fBall.reset());
		painter.mvAddStr(0,getWeight()-he.length()-1,he.c_str());

		painter.move(0,0);
		painter.addStr(("score: "+to_string(score)).c_str());
	}
	void keyEvent(KKeyEvent *e)override
	{
		bool flag=false;
		if(helpWindow->isAvailable())flag=true;
		switch(e->key)
		{
		case 'q':
			kApp->quit();
			break;
		case 'h':
		case '?':
			if(!helpWindow->isAvailable())
				helpWindow->show();
			else
				helpWindow->hide();
			break;
		case KEY_LEFT:
			if(flag)break;
			l-=lv;
			if(l<0)
				l=0;
			break;
		case KEY_RIGHT:
			if(flag)break;
			l+=lv;
			if(l+ll>getWeight())l=getWeight()-ll;
			break;
		case 'f':
			if(flag)break;
			if(vx<0)vx-=addv;
			else vx+=addv;
			break;
		case 's':
			if(flag)break;
			if(vx<0)vx+=addv;
			else vx-=addv;
			break;
		case 'F':
			if(flag)break;
			if(vy<0)vy-=addv;
			else vy+=addv;
			break;
		case 'S':
			if(flag)break;
			if(vy<0)vy+=addv;
			else vy-=addv;
			break;
		}
	}
public:
	MainWindow(KWidget *parent=nullptr):KWidget(0,0,0,0,parent)
	{
		srand(time(nullptr));
		x=getHeight()/2;
		y=getWeight()/2;
		vx=((double)rand()/RAND_MAX)*4.0-2.0;
		vy=((double)rand()/RAND_MAX)*2.0;
		l=getWeight()/2-ll/2;
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
			if(helpWindow->isAvailable())
			{
				repaint();
				usleep(50000);
				continue;
			}
			x+=vx/2;
			if(x<0)
			{
				x=0;
				vx=abs(vx);
			}
			else if(x>=getHeight()-1&&y>=l&&y<l+ll)
			{
				x=getHeight()-2;
				score+=100*(vx+vy);
				vx=-abs(vx);
			}
			else if(x>=getHeight())
			{
				x=getHeight()-1;
				score-=1000;
				vx=-abs(vx);
			}
			y+=vy;
			if(y<0)
			{
				y=0;
				vy=abs(vy);
			}
			else if(y>=getWeight()-1)
			{
				y=getWeight()-2;
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

