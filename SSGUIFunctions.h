#ifndef __SS_GUI_FUNCTIONS_H__
#define __SS_GUI_FUNCTIONS_H__

#include <irrlicht.h>

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;


// функция для получения свободного ID для элемента
s32 getFreeElementID(s32 needed, IGUIEnvironment *env);

// функция для получения свободного дочернего ID по заданому родительскому элементу
s32 getFreeChildElementID(IGUIElement *parent, IGUIEnvironment *env);

// функция для создания спрайтов
s32 createSprite(IGUISpriteBank *sprites, ITexture *texture, const array<rect<s32>> &rectangles = 0, u32 frameTime = 0, bool reverse = false);

void drawIGUIElementRect(IGUIEnvironment *environment, IGUIElement *element);


struct Indention
{
	Indention() {}
	Indention(s32 FIndention, s32 SIndention)
	{
		Indention::FIndention = FIndention;
		Indention::SIndention = SIndention;
	}
	bool operator ==(Indention obj)
	{
		if (FIndention == obj.FIndention && SIndention == obj.SIndention)
			return true;
		else
			return false;
	}
	bool operator !=(Indention obj)
	{
		if (FIndention != obj.FIndention || SIndention != obj.SIndention)
			return true;
		else
			return false;
	}
	s32 FIndention;
	s32 SIndention;
};

struct SideBarCaption
{
	IGUIFont *Font;
	SColor Color;
	const wchar_t *Caption;
	rect<s32> Rect;
	Indention HIndention;
	s32 VIndention;
	bool Center;
	bool Visible;
};

struct SSGUICaptionStructure
{
	const wchar_t *Text;
	IGUIFont *Font;
	SColor Color;
	rect<s32> Rect;
	bool HCener;
	bool VCenter;
};

struct SSGUIImageStructure
{
	ITexture *Image;
	rect<s32> Rect;
	bool HCenter;
	bool VCenter;
};

enum SSGUI_ALIGNMENT
{
	SSGUIA_UPPERLEFT = 0,
	SSGUIA_CENTER,
	SSGUIA_BOTTOMRIGHT
};


#endif