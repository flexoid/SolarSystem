#include "SSGUISideNavigateBar.h"

#include <irrlicht.h>

SSGUISideNavigateBar::SSGUISideNavigateBar(ITexture *image, IGUIEnvironment *environment, IGUIElement *parent, s32 id)
					:IGUIElement(EGUIET_ELEMENT, environment, parent, id, rect<s32>(0,0,0,0))
{
	Image = image;

	Displacement = 0;

	Container.Container = 0;

	Caption.Font = Environment->getSkin()->getFont();
	Caption.Color = SColor(255,255,255,255);
	Caption.Caption = 0;
	Caption.HIndention = Indention(1,1);
	Caption.VIndention = 1;
	Caption.Rect = rect<s32>(0,0,0,0);
	Caption.Center = false;
	Caption.Visible = true;

	LineColor = SColor(255,255,255,255);

	Callback = 0;

	neededState = 1;
	animSpeed = 1.0f;

	update();
}

SSGUISideNavigateBar::~SSGUISideNavigateBar()
{
}

void SSGUISideNavigateBar::setImage(ITexture *image)
{
	if (image)
	{
		Image = image;
		rebuild();
	}
}

void SSGUISideNavigateBar::setHIndention(s32 indention)
{
	HIndention = indention;

	rebuild();
}

void SSGUISideNavigateBar::setVIndention(s32 indention)
{
	VIndention = indention;

	rebuild();
}

void SSGUISideNavigateBar::setContainerHIndention(s32 indention)
{
	Indention OldIndention = Container.HIndention;

	if (indention < 1)
		Container.HIndention = Indention(1,1);
	else
		Container.HIndention = Indention(indention, indention);

	if (Container.HIndention != OldIndention)
		rebuild();
}

void SSGUISideNavigateBar::setContainerHIndention(s32 LeftIndention, s32 RightIndention)
{
	Indention OldIndention = Container.HIndention;

	if (LeftIndention < 1)
		Container.HIndention.FIndention = 1;
	else
		Container.HIndention.FIndention = LeftIndention;

	if (RightIndention < 1)
		Container.HIndention.SIndention = 1;
	else
		Container.HIndention.SIndention = RightIndention;

	if (Container.HIndention != OldIndention)
		rebuild();
}

void SSGUISideNavigateBar::setContainerVIndention(s32 indention)
{
	Indention OldIndention = Container.VIndention;

	if (indention < 1)
		Container.VIndention = Indention(1,1);
	else
		Container.VIndention = Indention(indention, indention);

	if (Container.VIndention != OldIndention)
		rebuild();
}

void SSGUISideNavigateBar::setContainerVIndention(s32 UpIndention, s32 DownIndention)
{
	Indention OldIndention = Container.VIndention;

	if (UpIndention < 1)
		Container.VIndention.FIndention = 1;
	else
		Container.VIndention.FIndention = UpIndention;

	if (DownIndention < 1)
		Container.VIndention.SIndention = 1;
	else
		Container.VIndention.SIndention = DownIndention;

	if (Container.VIndention != OldIndention)
		rebuild();
}

void SSGUISideNavigateBar::setLineBetweenGroupColor(SColor color)
{
	LineColor = color;
}

s32 SSGUISideNavigateBar::createGroup(const wchar_t *caption)
{
	s32 ID = getFreeGroupID();
	SideNavigateBarGroup group;

	group.Caption.Caption = caption;
	group.Caption.Center = false;
	group.Caption.Color = SColor(255,255,255,255);
	group.Caption.Font = Environment->getSkin()->getFont();
	group.Caption.HIndention = Indention(1,1);
	group.Caption.Rect = rect<s32>(0,0,0,0);
	group.Caption.VIndention = 1;
	group.Caption.Visible = true;

	group.Container = 0;
	group.ID = ID;

	Groups.push_back(group);

	rebuild();

	return ID;
}

void SSGUISideNavigateBar::setGroupCaption(s32 groupID, const wchar_t *caption, IGUIFont *font, SColor color, bool center)
{
	if (groupID < (s32)Groups.size())
	{
		s32 index = getGroupIndex(groupID);

		Groups[index].Caption.Caption = caption;
		Groups[index].Caption.Center = center;
		Groups[index].Caption.Color = color;
		if (font)
			Groups[index].Caption.Font = font;
		else
			Groups[index].Caption.Font = Environment->getSkin()->getFont();

		rebuild();
	}
}

s32 SSGUISideNavigateBar::addButtonToGroup(s32 groupID, IGUIButton *button, SSGUI_ALIGNMENT alignment)
{
	s32 groupIndex = getGroupIndex(groupID);
	if (groupIndex >= 0)
	{
		s32 ID = getFreeButtonID(groupID);
		SideNavigateBarGroupButton Button;
		if (button)
		{
			Button.Button = button;
			Button.Alignment = alignment;
			Button.ID = ID;

			Groups[groupIndex].Buttons.push_back(Button);

			rebuild();

			return ID;
		}
	}
	return -1;
}

void SSGUISideNavigateBar::setGroupButtonAlignment(s32 groupID, s32 buttonID, SSGUI_ALIGNMENT alignment)
{
	s32 groupIndex = getGroupIndex(groupID);
	if (groupIndex >= 0)
	{
		s32 buttonIndex = getButtonIndex(groupID, buttonID);
		if (buttonID >=0)
		{
			SSGUI_ALIGNMENT oldAlignment = Groups[groupIndex].Buttons[buttonIndex].Alignment;
			Groups[groupIndex].Buttons[buttonIndex].Alignment = alignment;
			if (Groups[groupIndex].Buttons[buttonIndex].Alignment != oldAlignment)
				rebuild();
		}
	}
}

bool SSGUISideNavigateBar::dropButtonFromGroup(s32 groupID, s32 buttonID)
{
	s32 groupIndex = getGroupIndex(groupID);
	if (groupIndex >= 0)
	{
		s32 buttonIndex = getButtonIndex(groupID, buttonID);
		if (buttonIndex >= 0)
		{
			if (Groups[groupIndex].Container->isMyChild(Groups[groupIndex].Buttons[buttonIndex].Button))
				Groups[groupIndex].Container->removeChild(Groups[groupIndex].Buttons[buttonIndex].Button);

			Groups[groupIndex].Buttons.erase(buttonIndex);

			rebuild();

			return true;
		}
	}
	return false;
}

void SSGUISideNavigateBar::setIntervalAfterGroupCaption(s32 interval)
{
	s32 OldInterval = IntervalAfterGroupCaption;

	if (interval < 1)
		IntervalAfterGroupCaption = 1;
	else
		IntervalAfterGroupCaption = interval;

	if (IntervalAfterGroupCaption != OldInterval)
		rebuild();
}

void SSGUISideNavigateBar::setIntervalBetweenGroupButtons(s32 interval)
{
	s32 OldInterval = IntervalBetweenGroupButtons;

	if (interval < 1)
		IntervalBetweenGroupButtons = 1;
	else
		IntervalBetweenGroupButtons = interval;

	if (IntervalBetweenGroupButtons != OldInterval)
		rebuild();
}

void SSGUISideNavigateBar::setIntervalBetweenGroups(s32 interval)
{
	s32 OldInterval = IntervalBetweenGroups;

	if (interval < 1)
		IntervalBetweenGroups = 1;
	else
		IntervalBetweenGroups = interval;

	if (IntervalBetweenGroups != OldInterval)
		rebuild();
}

void SSGUISideNavigateBar::setCallback(callback cb)
{
	Callback = cb;
}

void SSGUISideNavigateBar::rebuild()
{
	update();

	if (!Container.Container)
	{
		Container.Container = new IGUIElement(EGUIET_ELEMENT, Environment, this, -1, rect<s32>(0,0,0,0));
	}

// Caption
	if (Caption.Caption)
	{
		Caption.Rect = rect<s32>(0,0,0,0);
		Caption.Rect.UpperLeftCorner.X = AbsoluteRect.UpperLeftCorner.X + Caption.HIndention.FIndention;
		Caption.Rect.UpperLeftCorner.Y = AbsoluteRect.UpperLeftCorner.Y + Caption.VIndention;
		Caption.Rect.LowerRightCorner.X = AbsoluteRect.LowerRightCorner.X - Caption.HIndention.SIndention;
		Caption.Rect.LowerRightCorner.Y = Caption.Rect.UpperLeftCorner.Y + Caption.Font->getDimension(L"").Height;
	}
//--------

	Container.Container->setRelativePosition(rect<s32>(Container.HIndention.FIndention,
		Caption.Rect.LowerRightCorner.Y - AbsoluteRect.UpperLeftCorner.Y + Container.VIndention.FIndention,
		AbsoluteRect.getWidth() - Container.HIndention.SIndention,
		AbsoluteRect.getHeight() - Container.VIndention.SIndention));

	s32 gY = 0;

	for (s32 i = 0; i < (s32)Groups.size(); i++)
	{
		Groups[i].Caption.Rect.UpperLeftCorner.X =
			Container.Container->getAbsolutePosition().UpperLeftCorner.X + Groups[i].Caption.HIndention.FIndention;
		Groups[i].Caption.Rect.UpperLeftCorner.Y =
			Container.Container->getAbsolutePosition().UpperLeftCorner.Y + Groups[i].Caption.VIndention + gY;
		Groups[i].Caption.Rect.LowerRightCorner.X =
			Container.Container->getAbsolutePosition().LowerRightCorner.X - Groups[i].Caption.HIndention.SIndention;
		Groups[i].Caption.Rect.LowerRightCorner.Y =
			Groups[i].Caption.Rect.UpperLeftCorner.Y + Groups[i].Caption.Font->getDimension(L"").Height;

		if (!Groups[i].Container)
			Groups[i].Container = new IGUIElement(EGUIET_ELEMENT, Environment, Container.Container, -1, rect<s32>(0,0,0,0));

		rect<s32> GContainerRect;

		GContainerRect.UpperLeftCorner.X = 0;
		GContainerRect.UpperLeftCorner.Y = gY + Groups[i].Caption.Rect.getHeight() + IntervalAfterGroupCaption;
		GContainerRect.LowerRightCorner.X = Container.Container->getAbsolutePosition().getWidth();
		GContainerRect.LowerRightCorner.Y = GContainerRect.UpperLeftCorner.Y;

		Groups[i].Container->setRelativePosition(GContainerRect);

		s32 LastButtonIndex = -1;

		s32 bY = 0;

		for (s32 n = 0; n < (s32)Groups[i].Buttons.size(); n++)
		{
			if (!Groups[i].Container->isMyChild(Groups[i].Buttons[n].Button))
				Groups[i].Container->addChild(Groups[i].Buttons[n].Button);

			s32 X, Y;
			s32 Width = Groups[i].Buttons[n].Button->getAbsolutePosition().getWidth();
			s32 Height = Groups[i].Buttons[n].Button->getAbsolutePosition().getHeight();

			switch (Groups[i].Buttons[n].Alignment)
			{
			case SSGUIA_UPPERLEFT:
				X = 0;
				break;
			case SSGUIA_BOTTOMRIGHT:
				X = Groups[i].Container->getAbsolutePosition().getWidth() - Width;
				break;
			case SSGUIA_CENTER:
				X = s32((Groups[i].Container->getAbsolutePosition().getWidth() - Width) / 2);
				break;
			}

			Y = bY;

			Groups[i].Buttons[n].Button->setRelativePosition(rect<s32>(X, Y, X + Width, Y + Height));

			bY += Height + IntervalBetweenGroupButtons;

			LastButtonIndex = n;
		}

		if (LastButtonIndex >= 0)
			GContainerRect.LowerRightCorner.Y += Groups[i].Buttons[LastButtonIndex].Button->getAbsolutePosition().LowerRightCorner.Y -
			Groups[i].Container->getAbsolutePosition().UpperLeftCorner.Y;

		Groups[i].Container->setRelativePosition(GContainerRect);

		gY = Groups[i].Container->getRelativePosition().LowerRightCorner.Y + IntervalBetweenGroups;

		if (Container.Container->getAbsolutePosition().isPointInside(position2d<s32>(Container.Container->getAbsolutePosition().LowerRightCorner.X -1,
			Groups[i].Container->getAbsolutePosition().LowerRightCorner.Y)))
		{
			Groups[i].Container->setVisible(true);
			Groups[i].Caption.Visible = true;
		}
		else
		{
			Groups[i].Container->setVisible(false);
			Groups[i].Caption.Visible = false;
			break;
		}
	}
}

// Caption
void SSGUISideNavigateBar::setCaption(const wchar_t *caption, IGUIFont *font, SColor color)
{
	IGUIFont *lastFont = Caption.Font;

	Caption.Caption = caption;
	if (font)
		Caption.Font = font;
	else
		Caption.Font = Environment->getSkin()->getFont();
	Caption.Color = color;

	rebuild();
}

void SSGUISideNavigateBar::setCaptionHIndention(s32 indention)
{
	Indention OldIndention = Caption.HIndention;

	if (indention < 1)
		Caption.HIndention = Indention(1,1);
	else
		Caption.HIndention = Indention(indention, indention);

	if (Caption.HIndention != OldIndention)
		rebuild();
}

void SSGUISideNavigateBar::setCaptionHIndention(s32 LeftIndention, s32 RightIndention)
{
	Indention OldIndention = Caption.HIndention;

	if (LeftIndention < 1)
		Caption.HIndention.FIndention = 1;
	else
		Caption.HIndention.FIndention = LeftIndention;

	if (RightIndention < 1)
		Caption.HIndention.SIndention = 1;
	else
		Caption.HIndention.SIndention = RightIndention;

	if (Caption.HIndention != OldIndention)
		rebuild();
}

void SSGUISideNavigateBar::setCaptionVIndention(s32 indention)
{
	s32 OldIndention = Caption.VIndention;

	if (indention < 1)
		Caption.VIndention = 1;
	else
		Caption.VIndention = indention;

	if (Caption.VIndention != OldIndention)
		rebuild();
}

void SSGUISideNavigateBar::setCaptionCenterAlignment(bool center)
{
	Caption.Center = center;
}

void SSGUISideNavigateBar::update()
{
	if (Image)
	{
		dimension2d<s32> screenSize = Environment->getVideoDriver()->getScreenSize();
		s32 Width = Image->getOriginalSize().Width;
		s32 Height = Image->getOriginalSize().Height;

		rect<s32> rectangle;
		rectangle.UpperLeftCorner.X = screenSize.Width - HIndention - Width + Displacement;
		rectangle.UpperLeftCorner.Y = VIndention;
		rectangle.LowerRightCorner.X = rectangle.UpperLeftCorner.X + Width;
		rectangle.LowerRightCorner.Y = rectangle.UpperLeftCorner.Y + Height;

		IGUIElement::setRelativePosition(rectangle);
	}
}

bool SSGUISideNavigateBar::OnEvent(const SEvent &event)
{
	if (event.GUIEvent.EventType == EGET_BUTTON_CLICKED)
	{
		for (s32 i = 0; i < (s32)Groups.size(); i++)
		{
			for (s32 n = 0; n < (s32)Groups[i].Buttons.size(); n++)
			{
				if (Groups[i].Buttons[n].Button == event.GUIEvent.Caller)
				{
					if (Callback)
					{
						Callback(Groups[i].ID, Groups[i].Buttons[n].ID);
					}
					break;
				}
			}
		}

		return true;
	}
	return IGUIElement::OnEvent(event);
}

void SSGUISideNavigateBar::draw()
{
	IVideoDriver *driver = Environment->getVideoDriver();
	rect<s32> Resolution = rect<s32>(position2d<s32>(0,0), driver->getScreenSize());

	update();

	if (!Resolution.isPointInside(AbsoluteRect.UpperLeftCorner) &&
		!Resolution.isPointInside(AbsoluteRect.LowerRightCorner))
	{
		return;
	}

	if (Image && IsVisible)
	{
	// drawing background
		driver->draw2DImage(Image, AbsoluteRect.UpperLeftCorner, rect<s32>(position2d<s32>(0,0), Image->getOriginalSize()),
			0, SColor(255,255,255,255), true);

	// drawing caption
		if (Caption.Caption && Caption.Visible)
			Caption.Font->draw(Caption.Caption, Caption.Rect, Caption.Color, Caption.Center);


		position2d<s32> startLine, endLine;

		for (s32 i = 0; i < (s32)Groups.size(); i++)
		{
			if (Groups[i].Caption.Caption && Groups[i].Caption.Visible)
				Groups[i].Caption.Font->draw(Groups[i].Caption.Caption, Groups[i].Caption.Rect, Groups[i].Caption.Color, Groups[i].Caption.Center);

			startLine.X = AbsoluteRect.UpperLeftCorner.X + s32((Container.Container->getAbsolutePosition().UpperLeftCorner.X - AbsoluteRect.UpperLeftCorner.X) * 0.45f);
			startLine.Y = Caption.Rect.LowerRightCorner.Y + s32((AbsoluteRect.LowerRightCorner.Y - Caption.Rect.LowerRightCorner.Y) * 0.01f);
			endLine.X = startLine.X;
			endLine.Y = Groups[i].Caption.Rect.LowerRightCorner.Y - s32(Groups[i].Caption.Rect.getHeight() / 2);

			driver->draw2DLine(startLine, endLine, LineColor);

			startLine = endLine;
			endLine.X += s32((Container.Container->getAbsolutePosition().UpperLeftCorner.X - startLine.X) * 0.90f);
			
			driver->draw2DLine(startLine, endLine, LineColor);
		}

		IGUIElement::draw();
	}
}

void SSGUISideNavigateBar::show()
{
	neededState = 1;
}

void SSGUISideNavigateBar::showX()
{
	Displacement = 0;
	neededState = 1;
	rebuild();
}

void SSGUISideNavigateBar::hide()
{
	neededState = 0;
}

void SSGUISideNavigateBar::hideX()
{
	Displacement = HIndention + AbsoluteRect.getWidth();
	neededState = 0;
	rebuild();
}

void SSGUISideNavigateBar::setAnimationSpeed(f32 speed)
{
	animSpeed = speed;
}

void SSGUISideNavigateBar::OnPostRender(u32 timeMs)
{
	static s32 prevTime = -1;
	static bool animate = true;
	static s32 lastState = neededState;

	if (lastState != neededState)
	{
		animate = true;
		lastState = neededState;
	}

	if (prevTime < 0)
		prevTime = timeMs;

	dimension2d<s32> screenSize = Environment->getVideoDriver()->getScreenSize();

	f32 speed = animSpeed;

	if (animate)
	{
		s32 Width = AbsoluteRect.getWidth();

		if (neededState == 0)
		{
			Displacement += s32((50.0 / Width) * (timeMs - prevTime) * speed);

			if (Displacement > HIndention + Width)
			{
				Displacement = HIndention + Width;
				animate = false;
			}
		}
		else if (neededState == 1)
		{
			Displacement -= s32((50.0 / Width) * (timeMs - prevTime) * speed);

			if (Displacement < 0)
			{
				Displacement = 0;
				animate = false;
			}
		}
		else
		{
			neededState = 0;
		}

		rebuild();

	}

	prevTime = timeMs;
}

s32 SSGUISideNavigateBar::getFreeGroupID()
{
	s32 ID = -1;
	s32 id = 0;
	while (ID == -1)
	{
		bool avalible = true;
		for (s32 i = 0; i < (s32)Groups.size(); i++)
		{
			if (Groups[i].ID == id)
				avalible = false;
		}
		if (!avalible)
			id++;
		else
		{
			ID = id;
			break;
		}
	}
	return ID;
}

s32 SSGUISideNavigateBar::getGroupIndex(s32 groupID)
{
	for (s32 i = 0; i < (s32)Groups.size(); i++)
	{
		if (Groups[i].ID == groupID)
			return i;
	}
	return -1;
}

s32 SSGUISideNavigateBar::getFreeButtonID(s32 groupID)
{
	s32 groupIndex = getGroupIndex(groupID);
	if (groupIndex >= 0)
	{
		s32 ID = -1;
		s32 id = 0;
		while (ID == -1)
		{
			bool avalible = true;
			for (s32 i = 0; i < (s32)Groups[groupIndex].Buttons.size(); i++)
			{
				if (Groups[groupIndex].Buttons[i].ID == id)
					avalible = false;
			}
			if (!avalible)
				id++;
			else
			{
				ID = id;
				break;
			}
		}
		return ID;
	}
	else
		return -1;
}

s32 SSGUISideNavigateBar::getButtonIndex(s32 groupID, s32 buttonID)
{
	s32 groupIndex = getGroupIndex(groupID);
	if (groupIndex >= 0)
	{
		for (s32 i = 0; i < (s32)Groups[groupIndex].Buttons.size(); i++)
		{
			if (Groups[groupIndex].Buttons[i].ID == buttonID)
				return i;
		}
	}
	return -1;
}