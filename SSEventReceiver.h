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

extern f32 koeffOfDist;
extern ICameraSceneNode* camera;
extern s32 koeffOfScale;
extern f32 koeffSpeed;


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
						koeffOfScale = ZoomScrollBar->getPos();
						if (abs(ZoomScrollBar->getMax() / 2 - ZoomScrollBar->getPos()) <= 100)
							ZoomScrollBar->setPos(ZoomScrollBar->getMax() / 2);
					}

					else if (caller == DistanceScrollBar)
					{
						koeffOfDist = (f32)(DistanceScrollBar->getPos() / 1000.0f + 1.4f);
						if (abs(DistanceScrollBar->getMax() / 2 - DistanceScrollBar->getPos()) <= 100)
							DistanceScrollBar->setPos(DistanceScrollBar->getMax() / 2);
					}
					else if (caller == SpeedScrollBar)
					{
						if (SpeedScrollBar->getPos() < 15000)
						{
							koeffSpeed = (f32)(0.15f * 
								(1.0f + (SpeedScrollBar->getPos() / 1000.0f) / (5.0f - 4.0f / 15 * (SpeedScrollBar->getPos() / 1000.0f)))); 
						}
						else
							koeffSpeed = (f32)(0.15f * (1.0f + SpeedScrollBar->getPos() / 1000.0f)); 
					}
				}
			case EGET_BUTTON_CLICKED:
				{
					if (caller == SatelliteInfoButton)
					{
						SatelliteInfoWindow->show(InfoStructures[currentPlanetID].SatelliteInfo.SatelliteInfo);
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