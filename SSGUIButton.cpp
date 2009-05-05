#include "SSGUIButton.h"
#include "SSGUIFunctions.h"

#include <windows.h>

SSGUIButton::SSGUIButton(IGUIEnvironment *environment, IGUIElement *parent, s32 id)
			:IGUIElement(EGUIET_BUTTON, environment, parent, id, rect<s32>(0,0,0,0)),
			OverrideFont(0), OverrideColor(255,255,255,255),
			Pressed(false), IsPushButton(false),
			Hovered(false), WasPressed(false)
{

	IGUIElement::setTabStop(false);
}

SSGUIButton::~SSGUIButton()
{
	if (OverrideFont)
		OverrideFont->drop();

	for (s32 i = 0; i < SSGBS_COUNT; i++)
	{
		if (Image[i])
			Image[i]->drop();
	}
}

void SSGUIButton::setPosition(const position2d<s32> &position)
{
	rect<s32> rect;
	rect.UpperLeftCorner = position;
	rect.LowerRightCorner = position + position2d<s32>(IGUIElement::getRelativePosition().getWidth(), IGUIElement::getRelativePosition().getHeight());
	IGUIElement::setRelativePosition(rect);
}

void SSGUIButton::setOverrideFont(IGUIFont *font)
{
	if (OverrideFont)
		OverrideFont->drop();

	OverrideFont = font;

	if (OverrideFont)
		OverrideFont->grab();
}

void SSGUIButton::setOverrideColor(SColor color)
{
	OverrideColor = color;
}

void SSGUIButton::setIsPushButton(bool IsPushButton)
{
	SSGUIButton::IsPushButton = IsPushButton;
}

void SSGUIButton::setPressed(bool Pressed)
{
	SSGUIButton::Pressed = Pressed;
}

void SSGUIButton::setVisualState(SSGUI_BUTTON_STATE state, ITexture *image)
{
	if (Image[state])
		Image[state]->drop();

	Image[state] = image;

	if (image)
		ImageRect[state] = rect<s32>(position2d<s32>(0,0), image->getOriginalSize());

	if (Image[state])
		Image[state]->grab();

	if (state == SSGBS_BUTTON_UP)
		update();
}

void SSGUIButton::update()
{
	rect<s32> rectangle = IGUIElement::getRelativePosition();
	rectangle.LowerRightCorner = rectangle.UpperLeftCorner + position2d<s32>(Image[0]->getSize().Width, Image[0]->getSize().Height);
	IGUIElement::setRelativePosition(rectangle);
}

bool SSGUIButton::OnEvent(const SEvent &event)
{
	if (!IsEnabled)
		return Parent ? Parent->OnEvent(event) : false;

	switch(event.EventType)
	{
	case EET_GUI_EVENT:
		if (event.GUIEvent.EventType == EGET_ELEMENT_HOVERED)
		{
			if (!Pressed && (GetKeyState(VK_LBUTTON) == 0 || GetKeyState(VK_LBUTTON) == 1)) Hovered = true;
			if (WasPressed) setPressed(true);
		}

		if (event.GUIEvent.EventType == EGET_ELEMENT_LEFT)
		{
			WasPressed = Pressed;
			Hovered = false;
			setPressed(false);
		}
		break;
	case EET_MOUSE_INPUT_EVENT:
		if (event.MouseInput.Event == EMIE_LMOUSE_PRESSED_DOWN)
		{
			if (!IsPushButton)
				setPressed(true);

			Hovered = false;
			
			return true;
		}
		else
		if (event.MouseInput.Event == EMIE_LMOUSE_LEFT_UP)
		{
			bool wasPressed = Pressed;
			WasPressed = false;

			if ( !AbsoluteClippingRect.isPointInside( position2d<s32>(event.MouseInput.X, event.MouseInput.Y ) ) )
			{
				if (!IsPushButton)
					setPressed(false);
				Hovered = false;
				return true;
			}
			else
			{
				Hovered = true;
			}

			if (!IsPushButton)
				setPressed(false);
			else
			{
				setPressed(!Pressed);
			}
			
			if ((!IsPushButton && wasPressed && Parent) ||
				(IsPushButton && wasPressed != Pressed))
			{
				SEvent newEvent;
				newEvent.EventType = EET_GUI_EVENT;
				newEvent.GUIEvent.Caller = this;
				newEvent.GUIEvent.Element = 0;
				newEvent.GUIEvent.EventType = EGET_BUTTON_CLICKED;
				Parent->OnEvent(newEvent);
			}

			return true;
		}
		break;
	default:
		break;
	}

	return Parent ? Parent->OnEvent(event) : false;
}

void SSGUIButton::draw()
{
	if (!IsVisible)
		return;

	IGUISkin* skin = Environment->getSkin();
	IVideoDriver* driver = Environment->getVideoDriver();

	IGUIFont* font = OverrideFont;
	if (!OverrideFont)
		font = skin->getFont(EGDF_BUTTON);

	rect<s32> rect = AbsoluteRect;

	// todo:	move sprite up and text down if the pressed state has a sprite
	//			draw sprites for focused and mouse-over 

	ITexture *image;
	core::rect<s32> imageRect;

	if (Image[SSGBS_BUTTON_UP])
	{
		if (IsEnabled)
		{
			if (!Pressed)
			{
				if (Hovered && Image[SSGBS_BUTTON_MOUSE_OVER])
				{
					image = Image[SSGBS_BUTTON_MOUSE_OVER];
					imageRect = ImageRect[SSGBS_BUTTON_MOUSE_OVER];
				}
				else
				{
					image = Image[SSGBS_BUTTON_UP];
					imageRect = ImageRect[SSGBS_BUTTON_UP];
				}

				position2d<s32> UpperLeftCorner = rect.UpperLeftCorner - IGUIElement::getParent()->getAbsolutePosition().UpperLeftCorner;
				position2d<s32> LowerRightCorner = UpperLeftCorner + position2d<s32>(imageRect.getWidth(), imageRect.getHeight());

				IGUIElement::setRelativePosition(core::rect<s32>(UpperLeftCorner, LowerRightCorner));

				driver->draw2DImage(image, rect.UpperLeftCorner, imageRect, 0, SColor(255, 255, 255, 255), true);
			}
			else
			{
				if (Image[SSGBS_BUTTON_DOWN])
				{
					image = Image[SSGBS_BUTTON_DOWN];
					imageRect = ImageRect[SSGBS_BUTTON_DOWN];
				}
				else
				{
					image = Image[SSGBS_BUTTON_UP];
					imageRect = ImageRect[SSGBS_BUTTON_UP];
				}

				position2d<s32> UpperLeftCorner = rect.UpperLeftCorner - IGUIElement::getParent()->getAbsolutePosition().UpperLeftCorner;
				position2d<s32> LowerRightCorner = UpperLeftCorner + position2d<s32>(imageRect.getWidth(), imageRect.getHeight());

				IGUIElement::setRelativePosition(core::rect<s32>(UpperLeftCorner, LowerRightCorner));

				driver->draw2DImage(image, rect.UpperLeftCorner, imageRect, 0, SColor(255, 255, 255, 255), true);
			}
		}
		else
		{
			if (Image[SSGBS_BUTTON_INACTIVE])
			{
				image = Image[SSGBS_BUTTON_INACTIVE];
				imageRect = ImageRect[SSGBS_BUTTON_INACTIVE];
			}
			else
			{
				image = Image[SSGBS_BUTTON_UP];
				imageRect = ImageRect[SSGBS_BUTTON_UP];
			}

			position2d<s32> UpperLeftCorner = rect.UpperLeftCorner - IGUIElement::getParent()->getAbsolutePosition().UpperLeftCorner;
				position2d<s32> LowerRightCorner = UpperLeftCorner + position2d<s32>(imageRect.getWidth(), imageRect.getHeight());

			IGUIElement::setRelativePosition(core::rect<s32>(UpperLeftCorner, LowerRightCorner));

			driver->draw2DImage(image, rect.UpperLeftCorner, imageRect, 0, SColor(255, 255, 255, 255), true);
		}
	}

	if (Text.size())
	{
		rect = AbsoluteRect;
        if (Pressed)
			rect.UpperLeftCorner.Y += 2;

		if (font)
			font->draw(Text.c_str(), rect,	OverrideColor, true, true, &AbsoluteClippingRect);
	}

	IGUIElement::draw();
}