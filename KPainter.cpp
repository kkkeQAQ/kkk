#include "KPainter.h"

KPainter::KPainter(KWidget *widget)
{
	win=widget->win;
	wclear(win);
}

KPainter::~KPainter()
{
	wmove(win,LINES-1,COLS-1);
	wrefresh(win);
}

int KPainter::getXY(int &x,int &y)
{
	return getyx(win,x,y);
}

int KPainter::addCh(int ch)
{
	return waddch(win, ch);
}

int KPainter::mvAddCh(int x,int y,int ch)
{
	return mvwaddch(win, x, y, ch);
}

int KPainter::addStr(char* s)
{
	return waddstr(win, s);
}

int KPainter::move(int x,int y)
{
	return ::wmove(win,x,y);
}

int KPainter::mvAddStr(int x,int y,char *s)
{
	return mvwaddstr(win, x, y, s);
}

int KPainter::attrOn(chtype att)
{
	return wattron(win, att);
}

int KPainter::attrOff(chtype att)
{
	return wattroff(win, att);
}

int KPainter::attrSet(chtype att)
{
	return wattrset(win, att);
}


