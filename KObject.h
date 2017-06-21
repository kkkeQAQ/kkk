#ifndef KOBJECT_H
#define KOBJECT_H

#include <unordered_set>
#include "KEvent.h"
#include "KMutex.h"

class KObject{
private:
	KObject *parentP=nullptr;
	std::unordered_set<KObject*> childrenSet;
public:
	KObject(KObject *parent=nullptr);
	KObject(const KObject &object)=delete;
	virtual ~KObject();
	virtual void event(KEvent *event);
	void setParent(KObject *parent);
	KObject *parent();
	std::unordered_set<KObject*>& children();
};

#endif //KOBJECT_H
