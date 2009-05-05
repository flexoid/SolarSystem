#ifndef __SS_GUI_BUTTON_H_INCLUDED__
#define __SS_GUI_BUTTON_H_INCLUDED__

#include <irrlicht.h>

#include <IGUIButton.h>

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

enum SSGUI_BUTTON_STATE
	{
		//! The button is not pressed
		SSGBS_BUTTON_UP=0,
		//! The button is currently pressed down
		SSGBS_BUTTON_DOWN,
		//! The mouse cursor is over the button
		SSGBS_BUTTON_MOUSE_OVER,
		//! The mouse cursor is not over the button
		SSGBS_BUTTON_MOUSE_OFF,
		//! The button has the focus
		SSGBS_BUTTON_FOCUSED,
		//! The button doesn't have the focus
		SSGBS_BUTTON_NOT_FOCUSED,
		//! The button is inactive
		SSGBS_BUTTON_INACTIVE,
		//! not used, counts the number of enumerated items
		SSGBS_COUNT
	};

class SSGUIButton : public IGUIElement
{
public:
	explicit SSGUIButton(IGUIEnvironment *environment, IGUIElement *parent = 0, s32 id = -1);
			~SSGUIButton();

	void setPosition(const position2d<s32> &position);
	void update(void);
	void setVisualState(SSGUI_BUTTON_STATE state, ITexture *texture);
	void setOverrideFont(IGUIFont *font = 0);
	void setOverrideColor(SColor color);
	void setIsPushButton(bool IsPushButton);
	void setPressed(bool Pressed);

	virtual void draw(void);
	virtual bool OnEvent(const SEvent &event);


private:
	IGUIFont *OverrideFont;
	SColor OverrideColor;
	ITexture *Image[SSGBS_COUNT];
	rect<s32> ImageRect[SSGBS_COUNT];

	bool IsPushButton;
	bool Pressed;
	bool Hovered;
	bool WasPressed;
};

#endif