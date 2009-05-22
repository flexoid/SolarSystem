#ifndef __SS_FREE_FLIGHT_CAMERA_MODE_H_INCLUDED__
#define __SS_FREE_FLIGHT_CAMERA_MODE_H_INCLUDED__

#include <irrlicht.h>

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

class SSFreeFlightCameraMode : public IGUIElement
{
public:
	SSFreeFlightCameraMode(IGUIEnvironment *environment, ISceneManager *sceneManager, ICursorControl *cursorControl, const array<IGUIElement*> &GUIElements);
	~SSFreeFlightCameraMode();

	void On();
	void Off();

	void setSwitchONTime(u32 time);

	void setLabel(const wchar_t *text, IGUIFont *font = 0, SColor color = SColor(255,255,255,255));

	void addCameraSceneNodeAnimators(const array<ISceneNode*> &nodes);

	virtual void OnPostRender(u32 timeMs);

private:
	struct SSGUILabel
	{
		const wchar_t *Text;
		IGUIFont *Font;
		SColor Color;
		rect<s32> Rect;
	};

	struct RegisteredGUIElement
	{
		IGUIElement *Element;
		bool wasVisible;
	};

	u32 SwitchONTime;
	bool SwitchON;
	bool SwitchedON;
	SSGUILabel Label;

	ISceneManager *SceneManager;

	ICameraSceneNode *FPSCamera;

	ICameraSceneNode *AltCamera;
	ICursorControl *CursorControl;
	array<RegisteredGUIElement> GUIElements;
};

#endif