#ifndef __SS_GUI_ABOUT_WINDOW_H_INCLIDED__
#define __SS_GUI_ABOUT_WINDOW_H_INCLIDED__

#include <irrlicht.h>

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

class SSGUIAboutWindow : public IGUIElement
{
public:
	SSGUIAboutWindow(IGUIEnvironment *environment);
	~SSGUIAboutWindow();

	void setShowTime(u32 time);

	void show(const char *image);
	void hide();

	virtual void OnPostRender(u32 timeMs);
	virtual bool OnEvent(const SEvent &event);
	virtual void draw();

private:
	void setImage(const char *image);
	void update();

	IGUIButton *Button;
	ITexture *Image;
	u32 ShowTime;
	s32 Alpha;
	bool Show;
};

#endif