#ifndef __SS_GUI_SIDE_INFO_BAR_H_INCLUDED__
#define __SS_GUI_SIDE_INFO_BAR_H_INCLUDED__

#include <irrlicht.h>
#include <windows.h>

#include "SSGUIFunctions.h"

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

class SSGUISideInfoBar : public IGUIElement
{
public:
	SSGUISideInfoBar(IGUIEnvironment *environment, IGUIElement *parent);
	~SSGUISideInfoBar();

	virtual void OnPostRender(u32 timeMs);
	virtual void draw();
	virtual bool OnEvent(const SEvent &event);

	void setHIndention(s32 HIndention);
	void setVIndention(s32 VIndention);
	void setBackground(ITexture *titleBoxBackground, ITexture *imageBoxBackground, ITexture *ginfoBoxBackground, ITexture *phinfoBoxBackground);
	void setTitleBox(ITexture *image, SColor color = SColor(255,255,255,255));
	void setImageBox(ITexture *image, SColor color = SColor(255,255,255,255));
	void setGInfoBox(ITexture *image, SColor color = SColor(255,255,255,255));
	void setPHInfoBox(ITexture *image, SColor color = SColor(255,255,255,255));
	void setAnimationSpeed(f32 speed);

	ITexture* getTitleBox();
	ITexture* getImageBox();
	ITexture* getGInfoBox();
	ITexture* getPHInfoBox();

	void show();
	void showX();
	void hide();
	void hideX();

private:
	void update();
	void rebuild();

	struct SideInfoBarTitleBox
	{
		ITexture *Background;
		SSGUIImageStructure Image;
		SColor Color;
		rect<s32> Rect;
	};

	struct SideInfoBarImageBox
	{
		ITexture *Background;
		SSGUIImageStructure Image;
		SColor Color;
		rect<s32> Rect;
	};

	struct SideInfoBarGInfoBox
	{
		ITexture *Background;
		SSGUIImageStructure Image;
		SColor Color;
		rect<s32> Rect;
	};

	struct SideInfoBarPHInfoBox
	{
		ITexture *Background;
		SSGUIImageStructure Image;
		SColor Color;
		rect<s32> Rect;
	};

	struct SideInfoBarBoxesDisplacement
	{
		s32 TitleBox;
		s32 ImageBox;
		s32 GInfoBox;
		s32 PHInfoBox;
	};

	SideInfoBarTitleBox TitleBox;
	SideInfoBarImageBox ImageBox;
	SideInfoBarPHInfoBox PHInfoBox;
	SideInfoBarGInfoBox GInfoBox;

	SideInfoBarBoxesDisplacement Displacement;

	s32 IntervalBetweenBoxes;
	s32 HIndention;
	s32 VIndention;

	s32 neededState;
	f32 animSpeed;
	s32 Alpha;
};

#endif