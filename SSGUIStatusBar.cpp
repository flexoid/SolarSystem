#include "SSGUIStatusBar.h"
#include "SSGUIElementFactory.h"

SSGUIStatusBar::SSGUIStatusBar(IGUIEnvironment *environment, ICursorControl *cursorControl)
			: IGUIElement(EGUIET_ELEMENT, environment, environment->getRootGUIElement(), -1, rect<s32>(0,0,0,0)),
			HIndention(0), VIndention(0), HTextIndention(0)
{
	HelpText = L"Здесь отображаются подсказки к елементам навигации";

	CursorControl = cursorControl;

	Background = 0;

	Label.Font = Environment->getSkin()->getFont();
	Label.Color = SColor(255,255,255,255);
}

SSGUIStatusBar::~SSGUIStatusBar()
{
}

void SSGUIStatusBar::update()
{
	if (Background)
	{
		dimension2d<s32> screenSize = Environment->getVideoDriver()->getScreenSize();
		dimension2d<s32> size = Background->getOriginalSize();
		rect<s32> rectangle;
		rectangle.UpperLeftCorner.X = HIndention;
		rectangle.UpperLeftCorner.Y = screenSize.Height - VIndention - size.Height;
		rectangle.LowerRightCorner = rectangle.UpperLeftCorner + size;

		IGUIElement::setRelativePosition(rectangle);

		rectangle.UpperLeftCorner.X += HTextIndention;
		rectangle.LowerRightCorner.X -= HTextIndention;

		Label.Rect = rectangle;
	}
}

void SSGUIStatusBar::setBackground(ITexture *image)
{
	if (Background)
		Background->drop();

	Background = image;

	if (Background)
		Background->grab();

	update();
}

void SSGUIStatusBar::setIndention(s32 leftIndention, s32 bottomIndention)
{
	HIndention = leftIndention;
	VIndention = bottomIndention;

	update();
}

void SSGUIStatusBar::setTextAttributes(IGUIFont *font, SColor color, s32 HIndention)
{
	if (!font)
		font = Environment->getSkin()->getFont();

	Label.Font = font;
	Label.Color = color;
	HTextIndention = HIndention;

	update();
}

void SSGUIStatusBar::addElement(IGUIElement *element)
{
	if (RegisteredElements.binary_search(element) == -1)
		RegisteredElements.push_back(element);
}

void SSGUIStatusBar::removeElement(IGUIElement *element)
{
	s32 index = RegisteredElements.binary_search(element);

	if (index >= 0)
		RegisteredElements.erase(index);
}

void SSGUIStatusBar::draw()
{
	IVideoDriver *driver = Environment->getVideoDriver();

	if (!IsVisible)
		return;

	if (Background)
	{
		driver->draw2DImage(Background, AbsoluteRect.UpperLeftCorner, rect<s32>(position2d<s32>(0,0), Background->getOriginalSize()), 0, SColor(255,255,255,255), true);

		IGUIElement *ElementUnderCursor = Environment->getRootGUIElement()->getElementFromPoint(CursorControl->getPosition());

		s32 index = -1;
		
		while (ElementUnderCursor && ElementUnderCursor != this && ElementUnderCursor != Environment->getRootGUIElement() && index == -1)
		{
			index = RegisteredElements.binary_search(ElementUnderCursor);

			if (ElementUnderCursor != this && index == -1)
				ElementUnderCursor = ElementUnderCursor->getParent();
		}

		if (index >= 0 || ElementUnderCursor == this)
		{
			if (ElementUnderCursor->getType() == EGUIET_BUTTON)
				Label.Text = ((SSGUIButton*)ElementUnderCursor)->getHelpText().c_str();
			if (ElementUnderCursor->getType() == EGUIET_SCROLL_BAR)
				Label.Text = ((SSGUIScrollBar*)ElementUnderCursor)->getHelpText().c_str();
			if (ElementUnderCursor->getType() == EGUIET_WINDOW)
				Label.Text = ((SSGUISatelliteInfoWindow*)ElementUnderCursor)->getHelpText().c_str();
			if (ElementUnderCursor == this)
				Label.Text = HelpText.c_str();

			if (Label.Text)
				Label.Font->draw(Label.Text, Label.Rect, Label.Color, false, true);
		}
		else
			Label.Text = 0;
	}
}