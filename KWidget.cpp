#include "KWidget.h"

KWidget::KWidget(int x,int y,int height,int weight,KWidget *parent)
	:KObject(parent==nullptr?kApp:static_cast<KObject*>(parent)),
	x(x),y(y),height(height),weight(weight)
{
	KWidget *p=dynamic_cast<KWidget*>(KObject::parent());
	if(p==nullptr)win=newwin(height,weight,x,y);
	else win=derwin(p->win,height,weight,x,y);
	available=false;
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
			winMutex.lock();
			paintEvent(static_cast<KPaintEvent*>(e));
			for(auto i:children())
			{
				KWidget *w=dynamic_cast<KWidget*>(i);
				if(w!=nullptr)
				{
					w->event(e);
				}
			}
			wrefresh(win);
			winMutex.unlock();
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
	return height?height:LINES-x;
}

int KWidget::getWeight()
{
	return weight?weight:COLS-y;
}

void KWidget::setWindow(int x,int y,int height,int weight)
{
	winMutex.lock();
	wclear(win);
	wrefresh(win);
	if(this->height+1==height&&this->weight==weight)
	{
		this->x=x;
		this->y=y;
		mvwin(win,x,y);
	}
	else
	{
		this->x=x;
		this->y=y;
		this->height=height;
		this->weight=weight;
		KWidget *p=dynamic_cast<KWidget*>(KObject::parent());
		if(p==nullptr)win=newwin(height,weight,x,y);
		else win=derwin(p->win,height,weight,x,y);
	}
	winMutex.unlock();
	repaint();
}

