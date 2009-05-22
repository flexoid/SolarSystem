#ifndef __SS_GUI_SCROLLBAR_H_INCLUDED__
#define __SS_GUI_SCROLLBAR_H_INCLUDED__

#include <irrlicht.h>
#include <windows.h>

#include "SSGUIButton.h"

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

enum SSGUI_SCROLLBAR_STATES
{
	SSSS_SCROLLBAR_NORMAL = 0,
	SSSS_SCROLLBAR_INACTIVE,

	SSSS_COUNT
};

class SSGUIScrollBar : public IGUIScrollBar
{
public:
	explicit SSGUIScrollBar(bool horizontal, IGUIEnvironment *environment, IGUIElement *parent, s32 id, bool noclip = false);
			~SSGUIScrollBar();
	
	void setVisualElements(ITexture *ubs_up, ITexture *ubs_over, ITexture *ubs_down, ITexture *ubs_inactive,
		ITexture *dbs_up, ITexture *dbs_over, ITexture *dbs_down, ITexture *dbs_inactive,
		ITexture *rs_normal, ITexture *rs_inactive,
		ITexture *sls_normal, ITexture *sls_over, ITexture *sls_inactive);
	void setPosition(const position2d<s32> &pos);
	void setOrientation(bool horozontal);

	virtual s32 getMax() const;
	virtual void setMax(s32 max);
	virtual s32 getSmallStep() const;
	virtual void setSmallStep(s32 step);
	virtual s32 getLargeStep() const;
	virtual void setLargeStep(s32 step);
	virtual s32 getPos() const;
	virtual void setPos(s32 pos);

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

	enum SSGUI_SCROLLBAR_SLIDER_STATES
	{
		SSSSLS_SLIDER_NORMAL = 0,
		SSSSLS_SLIDER_MOUSE_OVER,
		SSSSLS_SLIDER_INACTIVE,

		SSSSLS_COUNT
	};

	s32 getPosFromMousePos(s32 x, s32 y) const;
	void refreshControls();

	SSGUIButton* UpButton;
	SSGUIButton* DownButton;

	ITexture *Rule[SSSS_COUNT];
	ITexture *Slider[SSSSLS_COUNT];

	rect<s32> SliderRect;

	bool Dragging;
	bool Horizontal;
	bool DraggedBySlider;
	bool TrayClick;
	bool SliderOver;
	s32 Pos;
	s32 SliderX;
	s32 SliderY;
	s32 Max;
	s32 SmallStep;
	s32 LargeStep;
	s32 DesiredPos;
	u32 LastChange;

	stringw HelpText;
};

#endif