#include "KWidget.h"

KWidget::KWidget(int x,int y,int height,int weight,KObject *parent)
	:KObject(parent==nullptr?kApp:parent),
	x(x),y(y),height(height),weight(weight),
	win(newwin(height,weight,x,y))
{
	available=true;
	wattroff(win,A_BLINK);
}

KWidget::~KWidget()
{
	delwin(win);
}

bool KWidget::isAvailable()
{
	return available;
}

void KWidget::show()
{
	available=true;
	repaint();
}

void KWidget::hide()
{
	available=false;
	wclear(win);
	wrefresh(win);
}

void KWidget::paintEvent(KPaintEvent *)
{
}

void KWidget::keyEvent(KKeyEvent *)
{
}

void KWidget::repaint()
{
	kApp->postEvent(this,new KPaintEvent());
}

void KWidget::event(KEvent *e)
{
	switch(e->type())
	{
	case KEvent::KeyEvent:
		keyEvent(static_cast<KKeyEvent*>(e));
		break;
	case KEvent::PaintEvent:
		if(available)
		{
			paintEvent(static_cast<KPaintEvent*>(e));
			for(auto i:children())
			{
				KWidget *w=static_cast<KWidget*>(i);
				if(w!=nullptr)
				{
					w->repaint();
				}
			}
		}
		break;
	default:
		break;
	}
}

int KWidget::getX()
{
	return x;
}

int KWidget::getY()
{
	return y;
}

int KWidget::getHeight()
{
	return height?height:LINES;
}

int KWidget::getWeight()
{
	return weight?weight:COLS;
}

void KWidget::setWindow(int x,int y,int height,int weight)
{
	this->x=x;
	this->y=y;
	this->height=height;
	this->weight=weight;
	repaint();
}

