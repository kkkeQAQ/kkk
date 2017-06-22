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
#include "KPainter.h"

KPainter::KPainter(KWidget *widget)
{
	win=widget->win;
	wattrset(win,0);
	wclear(win);
}

KPainter::~KPainter()
{
}

int KPainter::getXY(int &x,int &y)
{
	int res=getyx(win,x,y);
	return res;
}

int KPainter::box()
{
	return ::box(win,ACS_VLINE,ACS_HLINE);
}

int KPainter::addCh(int ch)
{
	return waddch(win, ch);
}

int KPainter::mvAddCh(int x,int y,int ch)
{
	return mvwaddch(win, x, y, ch);
}

int KPainter::addStr(const char* s)
{
	return waddstr(win, s);
}

int KPainter::move(int x,int y)
{
	return ::wmove(win,x,y);
}

int KPainter::mvAddStr(int x,int y,const char *s)
{
	return mvwaddstr(win, x, y, s);
}

int KPainter::setFont(KFont *font)
{
	if(has_colors())return wattrset(win,font->getStyle()|COLOR_PAIR(font->getColorNumber()));
	return wattrset(win,font->getStyle());
}

