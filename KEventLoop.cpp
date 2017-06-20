#include "KEventLoop.h"
#include "KApplication.h"

KEventLoop::KEventLoop(KObject *parent):KMutex(parent==nullptr?kApp:parent)
{
}

void KEventLoop::postEvent(KObject *object,KEvent *event)
{
	lock();
	q.emplace(object,event);
	unlock();
}

void KEventLoop::processEvent(KObject *parent,KObject *object,KEvent *event)
{
	if(object==parent)object->event(event);
	else
	{
		if(object==nullptr)parent->event(event);
		for(auto i:object->children())processEvent(i,object,event);
	}
}

void KEventLoop::processEvent()
{
	KObject *object;
	KEvent *event=nullptr;
	lock();
	if(!q.empty())
	{
		auto pair=q.front();q.pop();
		object=pair.first;
		event=pair.second;
	}
	unlock();
	if(event!=nullptr)
	{
		processEvent(parent(),object,event);
	}

}

void KEventLoop::exec()
{
	while(true)processEvent();
}

