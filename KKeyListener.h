#ifndef KKEYLISTENNER_H
#define KKEYLISTENNER_H

#include "KThread.h"

class KKeyListenner : public KThread{
public:
	KKeyListenner(KObject *parent=nullptr);
	void run()override;
};

#endif //KKEYLISTENNER_H
