#include "KEventLoop.h"
#include "KApplication.h"
#include "KQuitEvent.h"

KEventLoop::KEventLoop(KObject *parent):KObject(parent==nullptr?kApp:parent),semaphore(0)
{
}

void KEventLoop::postEvent(KObject *object,KEvent *event)
{
	mutex.lock();
	q.emplace(object,event);
	mutex.unlock();
	semaphore.release();
}

void KEventLoop::processEvent(KObject *parent,KObject *object,KEvent *event)
{
	if(object==parent)object->event(event);
	else
	{
		if(object==nullptr)parent->event(event);
		for(auto i:parent->children())processEvent(i,object,event);
	}
}

void KEventLoop::processEvent()
{
	KObject *object;
	KEvent *event=nullptr;
	mutex.lock();
	if(!q.empty())
	{
		auto pair=q.front();q.pop();
		object=pair.first;
		event=pair.second;
	}
	mutex.unlock();
	if(event!=nullptr)
	{
		processEvent(parent(),object,event);
		delete event;
	}

}

int KEventLoop::exec()
{
	KEvent *event=nullptr;
	while(true)
	{
		semaphore.require();
		mutex.lock();
		if(!q.empty())event=q.front().second;
		mutex.unlock();
		if(event!=nullptr)
		{
			if(event->type()==KEvent::QuitEvent)break;
			processEvent();
		}
	}
	KQuitEvent *quitEvent=static_cast<KQuitEvent*>(event);
	return quitEvent->exitCode;
}

