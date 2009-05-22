#ifndef __SS_GUI_SATELLITE_INFO_WINDOW_H_INCLUDED__
#define __SS_GUI_SATELLITE_INFO_WINDOW_H_INCLUDED__

#include <irrlicht.h>
#include <windows.h>

#include "SSGUIFunctions.h"

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

class SSGUISatelliteInfoWindow : public IGUIElement
{
public:
	SSGUISatelliteInfoWindow(IGUIEnvironment *environment);
	~SSGUISatelliteInfoWindow();

	void setShowTime(u32 time);

	void show(const char *image);
	void hide();

	virtual void OnPostRender(u32 timeMs);
	virtual bool OnEvent(const SEvent &event);
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
	void setImage(const char *image);
	void update();

	IGUIButton *Button;
	ITexture *Image;
	u32 ShowTime;
	s32 Alpha;
	bool Show;

	stringw HelpText;
};

#endif