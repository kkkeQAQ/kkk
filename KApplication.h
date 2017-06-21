#ifndef KAPPLICATION_H
#define KAPPLICATION_H

#include "KObject.h"
#include <vector>
#include "KEvent.h"
#include "KEventLoop.h"

class KApplication:public KObject{
private:
	std::vector<char*>args;
	static KApplication *self;
	KEventLoop *eventLoop;
public:
	static KApplication* instance();
	static void postEvent(KObject *object,KEvent *event);
	KApplication(int argc,char **argv);
	~KApplication()override;
	std::vector<char*>& arguments();
	void quit();
	void exit(int exitCode);
	int exec();
};

#define kApp KApplication::instance()

#endif //KAPPLICATION_H
