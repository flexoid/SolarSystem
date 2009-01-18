#pragma once
#include <irrlicht.h>

#ifndef __C_EVENT_DISPATCHER_H_INCLUDED__
#define __C_EVENT_DISPATCHER_H_INCLUDED__

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

class EventDispatcher : public IEventReceiver
{
public:
	bool (*eventHandler) (const SEvent& irrEvent);

private:

	virtual bool OnEvent (const SEvent& irrEvent)
	{
		return eventHandler(irrEvent);
	}
};
#endif