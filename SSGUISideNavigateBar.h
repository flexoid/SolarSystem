#ifndef __SS_GUI_SIDE_NAVIGATE_BAR_H_INCLUDED__
#define __SS_GUI_SIDE_NAVIGATE_BAR_H_INCLUDED__

#include <irrlicht.h>
#include <windows.h>

#include "SSGUIButton.h"
#include "SSGUIFunctions.h"

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

class SSGUISideNavigateBar : public IGUIElement
{
public:
	typedef void (*callback) (s32 groupID, s32 buttonID);

	SSGUISideNavigateBar(ITexture *image, IGUIEnvironment *environment, IGUIElement *parent, s32 id);
	~SSGUISideNavigateBar();

	virtual void draw();
	virtual bool OnEvent(const SEvent &event);
	virtual void OnPostRender(u32 timeMs);

	void setBackground(ITexture *image);

	void setHIndention(s32 indention);
	void setVIndention(s32 indention);

	void setLineBetweenGroupsColor(SColor color);

	void setCallback(callback cb);

	void setContainerHIndention(s32 indention);
	void setContainerHIndention(s32 LeftIndention, s32 RightIndention);
	void setContainerVIndention(s32 indention);
	void setContainerVIndention(s32 UpIndention, s32 DownIndention);

	void setCaption(const wchar_t *caption, IGUIFont *font = 0, SColor color = SColor(255,255,255,255));
	void setCaptionHIndention(s32 indention);
	void setCaptionHIndention(s32 LeftIndention, s32 RightIndention);
	void setCaptionVIndention(s32 indention);
	void setCaptionCenterAlignment(bool center);

	s32 createGroup(const wchar_t *caption);
	void setGroupCaption(s32 groupID, const wchar_t *caption);
	s32 addButtonToGroup(s32 groupID, IGUIButton *button, SSGUI_ALIGNMENT alignment = SSGUIA_UPPERLEFT);
	void setGroupButtonAlignment(s32 groupID, s32 buttonID, SSGUI_ALIGNMENT alignment);
	bool dropButtonFromGroup(s32 groupID, s32 buttonID);
	void setGroupsBoxCaptionFont(IGUIFont *font);
	void setGroupsBoxCaptionColor(SColor color);
	void setGroupsBoxCaptionHIndention(s32 indention);
	void setGroupsBoxCaptionHIndention(s32 leftIndention, s32 rightIndention);
	void setGroupsBoxCaptionVIndention(s32 indention);
	void setGroupsBoxCaptionCenter(bool center);
	void setGroupsBoxIntervalBetweenGroups(s32 interval);
	void setGroupsBoxIntervalAfterGroupCaption(s32 interval);
	void setGroupsBoxIntervalBetweenGroupButtons(s32 interval);

	void setSSButtonElementsForAll(ITexture *b_up, ITexture *b_mouse_over, ITexture *b_down, ITexture *b_inactive, IGUIFont *font, SColor color);

	void show();
	void showX();
	void hide();
	void hideX();
	void setAnimationSpeed(f32 speed);

	virtual const stringw & getHelpText() const
	{
		return HelpText;
	}

	virtual void setHelpText(wchar_t *text)
	{
		HelpText = text;
	}

private:
	void rebuild();
	void update();

	s32 getFreeGroupID();
	s32 getGroupIndex(s32 groupID);

	s32 getFreeButtonID(s32 groupID);
	s32 getButtonIndex(s32 groupID, s32 buttonID);

	struct SideNavigateBarGroup;
	struct SideNavigateBarGroupButton;
	struct SideNavigateBarContainer;

	struct SideNavigateBarCaption
	{
		const wchar_t *Caption;
		rect<s32> Rect;
		bool Visible;
	};

	struct SideNavigateBarGroup
	{
		SideNavigateBarCaption Caption;

		array<SideNavigateBarGroupButton> Buttons;

		IGUIElement *Container;

		s32 ID;
	};

	struct SideNavigateBarGroupsBox
	{
		array<SideNavigateBarGroup> Groups;

		IGUIFont *CaptionFont;
		SColor CaptionColor;

		Indention CaptionHIndention;
		s32 CaptionVIndention;
		bool CaptionCenter;

		s32 IntervalAfterGroupCaption;
		s32 IntervalBetweenGroups;
		s32 IntervalBetweenGroupButtons;
	};

	struct SideNavigateBarGroupButton
	{
		IGUIButton *Button;
		SSGUI_ALIGNMENT Alignment;

		s32 ID;
	};

	struct SideNavigateBarContainer
	{
		IGUIElement *Container;
		Indention HIndention;
		Indention VIndention;
	};

	s32 HIndention;
	s32 VIndention;
	s32 Displacement;

	ITexture *Background;

	SideBarCaption Caption;

	callback Callback;

	SideNavigateBarContainer Container;

	SideNavigateBarGroupsBox GroupsBox;

	SColor LineColor;

	s32 neededState;
	f32 animSpeed;

	stringw HelpText;
};

#endif