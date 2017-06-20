#ifndef KOBJECT_H
#define KOBJECT_H

#include <unordered_set>

class KObject{
private:
	KObject *parentP;
	std::unordered_set<KObject*> childrenSet;
public:
	KObject(KObject *parent=nullptr);
	KObject(const KObject &object)=delete;
	virtual ~KObject();
	void setParent(KObject *parent);
	KObject *parent();
	std::unordered_set<KObject*> children();
};

#endif //KOBJECT_H
