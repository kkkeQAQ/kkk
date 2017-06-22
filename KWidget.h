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
#ifndef KWIDGET_H
#define KWIDGET_H

#include "KObject.h"
#include "KApplication.h"
#include "KEvent.h"
#include "KKeyEvent.h"
#include "KPaintEvent.h"
#include <curses.h>
#include "KPainter.h"
#include "KMutex.h"

class KWidget : public KObject {
private:
	int x;
	int y;
	int height;
	int weight;
	KMutex winMutex;
	WINDOW *win;
	bool available;
protected:
	virtual void keyEvent(KKeyEvent *);
	virtual void paintEvent(KPaintEvent *);
public:
	friend class KPainter;
	int getX();
	int getY();
	int getHeight();
	int getWeight();
	bool isAvailable();
	void show();
	void hide();
	void setWindow(int x,int y,int height,int weight);
	KWidget(int x=0,int y=0,int height=0,int weight=0,KWidget *parent=nullptr);
	~KWidget()override;
	void repaint();
	void event(KEvent *)override;
};

#endif //KWIDGET_H
