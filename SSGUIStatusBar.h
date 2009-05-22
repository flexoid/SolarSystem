#ifndef __SS_GUI_STATUS_BAR_H_INCLUDED__
#define __SS_GUI_STATUS_BAR_H_INCLUDED__

#include <irrlicht.h>
#include <windows.h>

#include "SSGUIFunctions.h"

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

class SSGUIStatusBar : public IGUIElement
{
public:
	SSGUIStatusBar(IGUIEnvironment *environment, ICursorControl *cursorControl);
	~SSGUIStatusBar();

	void setBackground(ITexture *image);
	void setIndention(s32 leftIndention, s32 bottomIndention);
	void setTextAttributes(IGUIFont *font, SColor color = SColor(255,255,255,255), s32 HIndention = 0);
	void addElement(IGUIElement *element);
	void removeElement(IGUIElement *element);

	virtual void draw();

	virtual const stringw & getHelpText() const
	{
		return HelpText;
	}

	virtual void setHelpText(wchar_t *text)
	{
		HelpText = text;
	}

private:
	void update();

	ITexture *Background;

	ICursorControl *CursorControl;

	s32 HIndention;
	s32 VIndention;

	s32 HTextIndention;

	struct SSGUILabel
	{
		const wchar_t *Text;
		IGUIFont *Font;
		SColor Color;
		rect<s32> Rect;
	};

	SSGUILabel Label;

	stringw HelpText;

	array<IGUIElement*> RegisteredElements;
};

#endif