//											Обработчик событий

#ifndef __SS_EVENT_RECEIVER_H_INCLUDED__
#define __SS_EVENT_RECEIVER_H_INCLUDED__

#include <irrlicht.h>
#include "SSGUI.h"

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

extern IrrlichtDevice* device;
extern IVideoDriver* driver;
extern ISceneManager* smgr;
extern IGUIEnvironment* guienv;

class SSEventReceiver : public IEventReceiver
{
public:
	virtual bool OnEvent(const SEvent& event)
	{
		if (event.EventType == EET_GUI_EVENT)
		{
			// Обработка пользовательских сообщений
			IGUIElement *caller = event.GUIEvent.Caller;
			s32 id = event.GUIEvent.Caller->getID();
			IGUIEnvironment* env = device->getGUIEnvironment();
			
			switch(event.GUIEvent.EventType)
			{
			case EGET_SCROLL_BAR_CHANGED:
				{
					if (caller == ZoomScrollBar)
					{
					}
				}
			default:
				break;
			}
		}
		return false;
	}
};
#endif