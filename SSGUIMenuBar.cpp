#include "SSGUIMenuBar.h"

#include <irrlicht.h>

SSGUIMenuBar::SSGUIMenuBar(ITexture *image, IGUIEnvironment *environment, IGUIElement *parent, s32 id)
			:IGUIElement(EGUIET_ELEMENT, environment, parent, id, rect<s32>(0,0,0,0)),
			Interval(1), Horizontal(true), HIndention(1,1), VIndention(1,1), HCenter(false), VCenter(false)
{
	Background = image;

	update();
}

SSGUIMenuBar::~SSGUIMenuBar()
{
	if (Background) Background->drop();
	if (Separator) Separator->drop();
	if (Buttons.size() > 0)
	{
		for (s32 i = 0; i < (s32)Buttons.size(); i++)
		{
			Buttons[i].Button->drop();
		}
	}
}

void SSGUIMenuBar::update()
{
	if (Background)
	{
		position2d<s32> pos = IGUIElement::getRelativePosition().UpperLeftCorner;

		IGUIElement::setRelativePosition(rect<s32>(pos, pos + Background->getOriginalSize()));
	}
}

void SSGUIMenuBar::setOrientaiton(bool horizontal)
{
	Horizontal = horizontal;
	rebuild();
}

void SSGUIMenuBar::setBackground(ITexture *image)
{
	if (image)
	{
		Background = image;
		update();
		rebuild();
	}
}

void SSGUIMenuBar::setSeparator(ITexture *separator)
{
	if (separator)
	{
		Separator = separator;
		rebuild();
	}
}

void SSGUIMenuBar::setHIndention(s32 indention)
{
	Indention OldIndention = HIndention;

	if (indention < 1)
		HIndention = Indention(1, 1);
	else
		HIndention = Indention(indention, indention);

	if (HIndention != OldIndention)
		rebuild();
}

void SSGUIMenuBar::setHIndention(s32 LeftIndention, s32 RightIndention)
{
	Indention OldIndention = HIndention;

	if (LeftIndention < 1)
		HIndention.FIndention = 1;
	else
		HIndention.FIndention = LeftIndention;

	if (RightIndention < 1)
		HIndention.SIndention = 1;
	else
		HIndention.SIndention = RightIndention;

	if (HIndention != OldIndention)
		rebuild();
}

void SSGUIMenuBar::setVIndention(s32 indention)
{
	Indention OldIndention = VIndention;

	if (indention < 1)
		VIndention = Indention(1, 1);
	else
		VIndention = Indention(indention, indention);

	if (VIndention != OldIndention)
		rebuild();
}

void SSGUIMenuBar::setVIndention(s32 UpIndention, s32 DownIndention)
{
	Indention OldIndention = VIndention;

	if (UpIndention < 1)
		VIndention.FIndention = 1;
	else
		VIndention.FIndention = UpIndention;

	if (DownIndention < 1)
		VIndention.SIndention = 1;
	else
		VIndention.SIndention = DownIndention;

	if (VIndention != OldIndention)
		rebuild();
}

void SSGUIMenuBar::setInterval(s32 pixels)
{
	s32 OldInterval = Interval;

	if (pixels < 1)
		Interval = 1;
	else
		Interval = pixels;

	if (Interval != OldInterval)
		rebuild();
}

void SSGUIMenuBar::setIntervalAfterButton(s32 buttonID, s32 pixels)
{
	if (buttonID >= 0)
	{
		s32 index = getButtonIndex(buttonID);
		if (index != -1)
		{
			s32 OldInterval = Buttons[index].IntervalAfter;

			if (pixels < 0)
				Buttons[index].IntervalAfter = -1;
			else
				Buttons[index].IntervalAfter = pixels;

			if (Buttons[index].IntervalAfter != OldInterval)
				rebuild();
		}
	}
}

void SSGUIMenuBar::setHCenter(bool center)
{
	bool last = HCenter;

	HCenter = center;

	if (HCenter != last)
		rebuild();
}

void SSGUIMenuBar::setVCenter(bool center)
{
	bool last = VCenter;

	VCenter = center;

	if (VCenter != last)
		rebuild();
}

void SSGUIMenuBar::setSeparatorAfterButton(s32 buttonID, bool separator)
{
	if (buttonID >= 0)
	{
		s32 index = getButtonIndex(buttonID);
		if (index != -1)
		{
			bool last = Buttons[index].SeparatorAfter;
			Buttons[index].SeparatorAfter = separator;
			if (Buttons[index].SeparatorAfter != last)
				rebuild();
		}
	}
}

s32 SSGUIMenuBar::addButton(IGUIButton *button)
{
	if (button)
	{
		s32 ID = getFreeButtonID();

		SSMButton Button;
		Button.Button = button;
		Button.Callback = 0;
		Button.SeparatorAfter = false;
		Button.IntervalAfter = -1;
		Button.ID = ID;

		Buttons.push_back(Button);

		rebuild();

		return ID;
	}
	else
		return -1;
}

bool SSGUIMenuBar::dropButton(s32 buttonID)
{
	if (buttonID >= 0)
	{
		s32 index = getButtonIndex(buttonID);
		if(index != -1)
		{
			if (Container->isMyChild(Buttons[index].Button))
				Container->removeChild(Buttons[index].Button);

			Buttons.erase(index);

			rebuild();

			return true;
		}
	}
	return false;
}

void SSGUIMenuBar::rebuild()
{
	update();

	if (!Container)
	{
		Container = new IGUIElement(EGUIET_ELEMENT, Environment, this, -1, rect<s32>(0,0,0,0));
	}

	Container->setRelativePosition(rect<s32>(HIndention.FIndention, VIndention.FIndention,
		IGUIElement::getRelativePosition().getWidth() - HIndention.SIndention,
		IGUIElement::getRelativePosition().getHeight() - VIndention.SIndention));

	if (Horizontal)
	{
		s32 X = 0;
		s32 Y = 0;
		s32 lastButtonIndex = -1;

		for (s32 i = 0; i < (s32)Buttons.size(); i++)
		{
			s32 Width = Buttons[i].Button->getRelativePosition().getWidth();
			s32 Height = Buttons[i].Button->getRelativePosition().getHeight();

			if (Container->isPointInside(position2d<s32>(Container->getAbsolutePosition().UpperLeftCorner.X + X + Width,
				Container->getAbsolutePosition().UpperLeftCorner.Y)))
			{
				Container->addChild(Buttons[i].Button);

				if (VCenter)
					Y = s32((Container->getRelativePosition().getHeight() - Height) / 2);

				Buttons[i].Button->setRelativePosition(rect<s32>(X, Y, X + Width, Y + Height));

				Buttons[i].Button->setVisible(true);

				X += Width;

				if (Buttons[i].IntervalAfter != -1)
					X += Buttons[i].IntervalAfter;
				else
					X += Interval;

				if (Buttons[i].SeparatorAfter)
				{
					X += Separator->getSize().Width;

					if (Buttons[i].IntervalAfter != -1)
						X += Buttons[i].IntervalAfter;
					else
						X += Interval;
				}

				lastButtonIndex = i;
			}
			else
			{
				for (; i < (s32)Buttons.size(); i++)
					Buttons[i].Button->setVisible(false);
				break;
			}
		}

		if (HCenter)
		{
			if (lastButtonIndex != -1)
			{
				rect<s32> rectangle = Container->getRelativePosition();
				rectangle.LowerRightCorner.X = rectangle.UpperLeftCorner.X + Buttons[lastButtonIndex].Button->getRelativePosition().LowerRightCorner.X;
				s32 Width = rectangle.getWidth();
				rectangle.UpperLeftCorner.X = s32((IGUIElement::getRelativePosition().getWidth() - rectangle.getWidth()) / 2);
				rectangle.LowerRightCorner.X = rectangle.UpperLeftCorner.X + Width;

				Container->setRelativePosition(rectangle);
			}
		}
	}

	else
	{
		s32 X = 0;
		s32 Y = 0;
		s32 lastButtonIndex = -1;

		for (s32 i = 0; i < (s32)Buttons.size(); i++)
		{
			s32 Width = Buttons[i].Button->getRelativePosition().getWidth();
			s32 Height = Buttons[i].Button->getRelativePosition().getHeight();

			if (Container->isPointInside(position2d<s32>(Container->getAbsolutePosition().UpperLeftCorner.X,
				Container->getAbsolutePosition().UpperLeftCorner.Y + Y + Height)))
			{
				Container->addChild(Buttons[i].Button);

				if (HCenter)
					X = s32((Container->getRelativePosition().getWidth() - Width) / 2);

				Buttons[i].Button->setRelativePosition(rect<s32>(X, Y, X + Width, Y + Height));

				Buttons[i].Button->setVisible(true);

				Y += Height;

				if (Buttons[i].IntervalAfter != -1)
					Y += Buttons[i].IntervalAfter;
				else
					Y += Interval;

				if (Buttons[i].SeparatorAfter)
				{
					Y += Separator->getSize().Height;

					if (Buttons[i].IntervalAfter != -1)
						Y += Buttons[i].IntervalAfter;
					else
						Y += Interval;
				}

				lastButtonIndex = i;
			}
			else
			{
				for (; i < (s32)Buttons.size(); i++)
					Buttons[i].Button->setVisible(false);
				break;
			}
		}

		if (VCenter)
		{
			if (lastButtonIndex != -1)
			{
				rect<s32> rectangle = Container->getRelativePosition();
				rectangle.LowerRightCorner.Y = rectangle.UpperLeftCorner.Y + Buttons[lastButtonIndex].Button->getRelativePosition().LowerRightCorner.Y;
				s32 Height = rectangle.getHeight();
				rectangle.UpperLeftCorner.Y = s32((IGUIElement::getRelativePosition().getHeight() - rectangle.getHeight()) / 2);
				rectangle.LowerRightCorner.Y = rectangle.UpperLeftCorner.Y + Height;

				Container->setRelativePosition(rectangle);
			}
		}
	}
}

void SSGUIMenuBar::setCallback(s32 buttonID, callback cb)
{
	if (buttonID >= 0)
	{
		s32 index = getButtonIndex(buttonID);
		if (index != -1)
		{
			Buttons[index].Callback = cb;
		}
	}
}

s32 SSGUIMenuBar::getButtonIndex(s32 ID)
{
	for (s32 i = 0; i < (s32)Buttons.size(); i++)
	{
		if (Buttons[i].ID == ID)
			return i;
	}
	return -1;
}

s32 SSGUIMenuBar::getFreeButtonID()
{
	s32 ID = -1;
	s32 id = 0;
	while (ID == -1)
	{
		bool avalible = true;
		for (s32 i = 0; i < (s32)Buttons.size(); i++)
		{
			if (Buttons[i].ID == id)
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

void SSGUIMenuBar::draw()
{
	IVideoDriver *driver = Environment->getVideoDriver();
	if (Background)
	{
		driver->draw2DImage(Background, AbsoluteRect.UpperLeftCorner, rect<s32>(position2d<s32>(0,0), Background->getOriginalSize()),
			0, SColor(255,255,255,255), true);

		if (Horizontal)
		{
			if (Separator)
			{
				for (s32 i = 0; i < (s32)Buttons.size(); i++)
				{
					if (Buttons[i].SeparatorAfter)
					{
						position2d<s32> pos = Container->getAbsolutePosition().UpperLeftCorner;
						pos.X += Buttons[i].Button->getRelativePosition().LowerRightCorner.X;
						if (Buttons[i].IntervalAfter != -1)
							pos.X += Buttons[i].IntervalAfter;
						else
							pos.X += Interval;

						pos.Y += s32((Container->getRelativePosition().getHeight() - Separator->getSize().Height) / 2);

						driver->draw2DImage(Separator, pos, rect<s32>(0, 0, Separator->getSize().Width, Separator->getSize().Height),
							0, SColor(255,255,255,255), true);
					}
				}
			}
		}
		else
		{
			if (Separator)
			{
				for (s32 i = 0; i < (s32)Buttons.size(); i++)
				{
					if (Buttons[i].SeparatorAfter)
					{
						position2d<s32> pos = Container->getAbsolutePosition().UpperLeftCorner;
						pos.X += s32((Container->getRelativePosition().getWidth() - Separator->getSize().Width) / 2);

						pos.Y += Buttons[i].Button->getRelativePosition().LowerRightCorner.Y;
						if (Buttons[i].IntervalAfter != -1)
							pos.Y += Buttons[i].IntervalAfter;
						else
							pos.Y += Interval;

						driver->draw2DImage(Separator, pos, rect<s32>(0, 0, Separator->getSize().Width, Separator->getSize().Height),
							0, SColor(255,255,255,255), true);
					}
				}
			}
		}

		IGUIElement::draw();

	}
}

bool SSGUIMenuBar::OnEvent(const SEvent &event)
{
	if (event.GUIEvent.EventType == EGET_BUTTON_CLICKED)
	{
		for (s32 i = 0; i < (s32)Buttons.size(); i++)
		{
			if (Buttons[i].Button == event.GUIEvent.Caller)
			{
				if (Buttons[i].Callback)
				{
					Buttons[i].Callback();
				}
				break;
			}
		}

		return true;
	}
	return IGUIElement::OnEvent(event);
}

void SSGUIMenuBar::deserializeAttributes(IAttributes *in, SAttributeReadWriteOptions *options)
{
	IVideoDriver *driver = Environment->getVideoDriver();

	Background = driver->getTexture(in->getAttributeAsString("background").c_str());
	Separator = driver->getTexture(in->getAttributeAsString("separator").c_str());
	HIndention = Indention(in->getAttributeAsInt("leftindention"), in->getAttributeAsInt("rightindention"));
	VIndention = Indention(in->getAttributeAsInt("topindention"), in->getAttributeAsInt("bottomindention"));
	HCenter = in->getAttributeAsBool("hcenter");
	VCenter = in->getAttributeAsBool("vcenter");

	rebuild();
}