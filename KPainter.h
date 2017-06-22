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
#ifndef KPAINTER_H
#define KPAINTER_H

#include "KObject.h"
#include "KWidget.h"
#include "curses.h"
#include "KFont.h"

class KWidget;

class KPainter : public KObject{
private:
	WINDOW *win;
public:
	KPainter(KWidget *widget);
	~KPainter()override;
	int move(int x,int y);
	int box();
	int getXY(int &x,int &y);
	int addCh(int ch);
	int mvAddCh(int x,int y,int ch);
	int addStr(const char* s);
	int mvAddStr(int x,int y,const char *s);
	int setFont(KFont *font);
};

#endif //KPAINTER_H
