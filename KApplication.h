#ifndef KAPPLICATION_H
#define KAPPLICATION_H

#include <vector>

class KApplication{
private:
	std::vector<char*>args;
	static KApplication *self;
public:
	static KApplication* instance();
	KApplication(int argc,char **argv);
	virtual ~KApplication();
	std::vector<char*>& arguments();
	int exec();
};

#define kApp KApplication::instance()

#endif //KAPPLICATION_H
