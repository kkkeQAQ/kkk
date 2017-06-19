#ifndef KAPPLICATION_H
#define KAPPLICATION_H

class KApplicatioin{
private:
	int argc;
	char **argv;
public:
	KApplicatioin(int argc,char **argv);
	virtual ~KApplicatioin();
	int exec();
};

#endif //KAPPLICATION_H
