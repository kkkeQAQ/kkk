#ifndef KEVENT_H
#define KEVENT_H

class KEvent{
public:
	enum EventType{Event,QuitEvent,PaintEvent,KeyEvent};
	virtual ~KEvent(){};
	virtual EventType type()
	{
		return Event;
	}
};

#endif //KEVENT_H
