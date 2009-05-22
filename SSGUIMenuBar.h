#ifndef __SS_GUI_MENUBAR_H_INCLUDED__
#define __SS_GUI_MENUBAR_H_INCLUDED__

#include <irrlicht.h>
#include <windows.h>

#include "SSGUIFunctions.h"

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

class SSGUIMenuBar : public IGUIElement
{
public:
	typedef void (*callback) (void);

	SSGUIMenuBar(ITexture *image, IGUIEnvironment *environment, IGUIElement *parent, s32 id);
	~SSGUIMenuBar();

	virtual void draw();
	virtual bool OnEvent(const SEvent &event);
	
	void setOrientaiton(bool horizontal);
	void setBackground(ITexture *image);
	void setSeparator(ITexture *separator);
	void setHIndention(s32 indention);
	void setHIndention(s32 LeftIndention, s32 RightIndention);
	void setVIndention(s32 indention);
	void setVIndention(s32 UpIndention, s32 DownIndention);
	void setInterval(s32 pixels);
	void setIntervalAfterButton(s32 buttonID, s32 pixels);
	void setSeparatorAfterButton(s32 buttonID, bool separator);
	void setHCenter(bool center);
	void setVCenter(bool center);
	s32 addButton(IGUIButton *button);
	bool dropButton(s32 buttonID);
	void setCallback(s32 buttonID, callback cb);

	virtual const stringw & getHelpText() const
	{
		return HelpText;
	}

	virtual void setHelpText(wchar_t *text)
	{
		HelpText = text;
	}

private:
	void update(void);
	void rebuild(void);

	IGUIElement *Container;

//-------------------------------------
	struct SSMButton
	{
		IGUIButton *Button;
		bool SeparatorAfter;
		callback Callback;
		s32 IntervalAfter;
		s32 ID;
	};

	array<SSMButton> Buttons;

	s32 getButtonIndex(s32 ID);
	s32 getFreeButtonID();
//-------------------------------------

	ITexture *Background;
	ITexture *Separator;
	bool Horizontal;
	s32 Interval;
	Indention HIndention;
	Indention VIndention;
	bool HCenter;
	bool VCenter;

	stringw HelpText;
};

#endif