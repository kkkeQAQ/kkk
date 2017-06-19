#ifndef KAPPLICATION_H
#define KAPPLICATION_H

#include "KObject.h"
#include <vector>

class KApplication:public KObject{
private:
	std::vector<char*>args;
	static KApplication *self;
public:
	static KApplication* instance();
	KApplication(int argc,char **argv);
	std::vector<char*>& arguments();
	int exec();
};

#define kApp KApplication::instance()

#endif //KAPPLICATION_H
