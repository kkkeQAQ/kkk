#include "KObject.h"

KObject::KObject(KObject *parent)
{
	setParent(parent);
}

KObject::~KObject()
{
	if(parentP!=nullptr)
	{
		parentP->children().erase(this);
	}
	while(!children().empty())delete *children().begin();
}

void KObject::event(KEvent *)
{
}

void KObject::setParent(KObject *parent)
{
	if(parentP!=nullptr)parentP->children().erase(this);
	parentP=parent;
	if(parentP!=nullptr)
	{
		parentP->children().insert(this);
	}
}

KObject* KObject::parent()
{
	return parentP;
}

std::unordered_set<KObject*>& KObject::children()
{
	return childrenSet;
}

