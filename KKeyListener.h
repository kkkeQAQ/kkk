#ifndef KKEYLISTENNER_H
#define KKEYLISTENNER_H

#include "KThread.h"

class KKeyListenner : public KThread{
private:
	bool flag=true;
public:
	KKeyListenner(KObject *parent=nullptr);
	~KKeyListenner()override;
	void run()override;
};

#endif //KKEYLISTENNER_H
