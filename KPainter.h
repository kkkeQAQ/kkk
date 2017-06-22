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
