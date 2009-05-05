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
	void setBackground(ITexture *titleBoxBackground, ITexture *imageBoxBackground, ITexture *phinfoBoxBackground, ITexture *ginfoBoxBackground);
	void setTitleBoxCaption(const wchar_t *text, IGUIFont *font = 0, SColor color = SColor(255,255,255,255));
	void setImageBoxImageBackground(ITexture *image);
	void setImageBoxImage(ITexture *image);
	void setImageBoxIcon(ITexture *icon);
	void setPHInfoBoxTextBoxAttributes(s32 HIndention = 0, s32 VIndention = 0, IGUIFont *font = 0, SColor color1 = SColor(255,255,255,255), SColor color2 = SColor(255,255,255,255));
	s32 addPHInfoBoxTextBlock(wchar_t *text1, wchar_t *text2, s32 id = -1);
	void setGInfoBoxText(wchar_t *text, IGUIFont *font = 0, SColor color = SColor(255,255,255,255));

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
		SSGUICaptionStructure Caption;
		rect<s32> Rect;
	};

	struct SideInfoBarImageBox
	{
		ITexture *Background;
		SSGUIImageStructure ImageBackground;
		SSGUIImageStructure Image;
		SSGUIImageStructure Icon;
		rect<s32> Rect;
	};

	struct SideInfoBarPHInfoBoxTextBlockStructure
	{
		wchar_t *Text;
		rect<s32> Rect;
	};

	struct SideInfoBarPHInfoBoxTextStructure
	{
		SideInfoBarPHInfoBoxTextBlockStructure Left;
		SideInfoBarPHInfoBoxTextBlockStructure Right;

		rect<s32> Rect;
	};

	struct SideInfoBarPHInfoBoxText
	{
		array<SideInfoBarPHInfoBoxTextStructure> TextBox;

		IGUIFont *Font;
		SColor ColorLeft;
		SColor ColorRight;

		s32 IntervalBetweenLines;

		s32 HIndention;
		s32 VIndention;

		rect<s32> Rect;
	};

	struct SideInfoBarPHInfoBox
	{
		ITexture *Background;
		SideInfoBarPHInfoBoxText TextBox;
		rect<s32> Rect;
	};

	struct SideInfoBarGInfoBox
	{
		ITexture *Background;
		IGUIStaticText *Text;
		rect<s32> Rect;
	};

	struct SideInfoBarBoxesDisplacement
	{
		s32 TitleBox;
		s32 ImageBox;
		s32 PHInfoBox;
		s32 GInfoBox;
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