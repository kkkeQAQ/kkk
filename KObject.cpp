#include "KObject.h"

KObject::KObject(KObject *parent)
{
	setParent(parent);
}

KObject::~KObject()
{
	while(!childrenSet.empty())delete *childrenSet.begin();
	parentP->childrenSet.erase(this);
}

void KObject::setParent(KObject *parent)
{
	parentP=parent;
	if(parentP!=nullptr)
	{
		parentP->childrenSet.insert(this);
	}
}

KObject* KObject::parent()
{
	return parentP;
}

std::unordered_set<KObject*> KObject::children()
{
	return childrenSet;
}

