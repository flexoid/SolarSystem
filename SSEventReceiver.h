//											Обработчик событий

#pragma once
#include <irrlicht.h>

#ifndef __C_SS_EVENT_RECEIVER_H_INCLUDED__
#define __C_SS_EVENT_RECEIVER_H_INCLUDED__

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
			s32 id = event.GUIEvent.Caller->getID();
			IGUIEnvironment* env = device->getGUIEnvironment();
			
			/*switch(event.GUIEvent.EventType)
			{
				//id элемента управления
			default:
				break;
			}*/
		}
		return false;
	}
};
#endif