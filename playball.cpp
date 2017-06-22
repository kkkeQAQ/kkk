/**
 * Copyright (C) 2017 kkkeQAQ <kkke@nwsuaf.edu.cn>.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 **/
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
#include <unistd.h>
#include <ctime>
#include <stdlib.h>

#include "KThread.h"
#include "KApplication.h"
#include "KKeyListener.h"
#include "KKeyEvent.h"
#include "KWidget.h"
#include "KPainter.h"
#include "KFont.h"
#include "KMutex.h"

#include "args/args.hxx"

#define SCORE(vx,vy,w) ((abs(vx)*abs(vy)*((w)-22.0))/2.0)

using namespace std;

const string version="v1.0";

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
		"",
		"score += (abs(vx)*abs(vy)*windowWeight-20)/2"
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
	KMutex mutex;
	double x=0,y=0,vx=0,vy=0,addv=1;
	int l=0,ll=20,lv=4;
	int score=0;
	int addScore=0,echoTime=0;
protected:
	void paintEvent(KPaintEvent *)override
	{
		int h=helpWindow->getHeight();
		int w=helpWindow->getWeight();
		helpWindow->setWindow(getHeight()/2-h/2,getWeight()/2-w/2,h,w);
		KPainter painter(this);
		KFont fBall(KFont::YELLOW,KFont::YELLOW);
		KFont fPlayer(KFont::RED,KFont::BLUE);
		painter.setFont(&fBall);
		painter.mvAddStr(x,y,"  ");

		string s;
		if(echoTime)
		{
			echoTime--;
			if(addScore<0)fPlayer|=KFont::HIGHLIGHT;
			else s="+";
			s+=to_string(addScore);
		}
		painter.setFont(&fPlayer);
		painter.move(getHeight()-1,l);
		int halfl=(ll-(int)s.length())/2;
		for(int i=0;i<halfl;i++)painter.addCh(' ');
		painter.addStr(s.c_str());
		for(int i=halfl+s.length();i<ll;i++)painter.addCh(' ');

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
			mutex.unlock();
			kApp->quit();
			break;
		case 'h':
		case '?':
			if(!helpWindow->isAvailable())
			{
				mutex.lock();
				helpWindow->show();
			}
			else
			{
				helpWindow->hide();
				mutex.unlock();
			}
			break;
		case KEY_LEFT:
			if(flag)break;
			l-=lv;
			if(l<0)l=0;
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
		vx=((double)rand()/RAND_MAX)*8.0-4.0;
		vy=((double)rand()/RAND_MAX)*4.0;
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
			mutex.lock();
			if(l<0)l=0;
			if(l+ll>getWeight())l=getWeight()-ll;
			x+=vx/2;
			if(x<0)
			{
				x=0;
				vx=abs(vx);
			}
			else if(x>=getHeight()-1&&y+1>=l&&y<l+ll)
			{
				x=getHeight()-2;
				addScore=SCORE(vx,vy,getWeight());
				vx=-abs(vx);
				score+=addScore;
				echoTime=10;
			}
			else if(x>=getHeight())
			{
				x=getHeight()-1;
				addScore=-1000;
				vx=-abs(vx);
				score+=addScore;
				echoTime=10;
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
			mutex.unlock();
			usleep(50000);
		}
	}

};

void argsParse(int argc,char **argv)
{
	args::ArgumentParser parser(string("playball ")+version);
	args::HelpFlag help(parser,"help","Show this help menu.",{'h',"help"});
	args::Flag fVersion(parser,"version","Show version",{'v',"version"});
	try{
		parser.ParseCLI(argc,argv);
	}
	catch(args::Help e)
	{
		cout<<parser;
		exit(0);
	}
	catch(args::ParseError e)
	{
		cerr<<e.what()<<endl;
		cerr<<parser;
		exit(1);
	}
	catch(args::ValidationError e)
	{
		cerr<<e.what()<<endl;
		cerr<<parser;
		exit(1);
	}
	if(fVersion)
	{
		cout<<version<<endl;
		exit(0);
	}
}

int main(int argc,char** argv)
{
	argsParse(argc,argv);
	KApplication a(argc,argv);
	MainWindow w;
	w.show();
	return a.exec();
}

