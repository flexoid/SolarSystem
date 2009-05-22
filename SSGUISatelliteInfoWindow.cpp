#include "SSGUISatelliteInfoWindow.h"

#include <windows.h>
#include <iostream>

SSGUISatelliteInfoWindow::SSGUISatelliteInfoWindow(IGUIEnvironment *environment)
						: IGUIElement(EGUIET_WINDOW, environment, environment->getRootGUIElement(), -1, rect<s32>(0,0,0,0)),
						Image(0), Alpha(0), ShowTime(1000), Show(false)
{
	this->setVisible(false);

	this->setRelativePosition(rect<s32>(position2d<s32>(0,0), Environment->getVideoDriver()->getScreenSize()));

	Button = Environment->addButton(rect<s32>(0,0,0,0), this);
	Button->setDrawBorder(false);
	Button->setVisible(false);

	update();
}

SSGUISatelliteInfoWindow::~SSGUISatelliteInfoWindow()
{
}

void SSGUISatelliteInfoWindow::update()
{
	dimension2d<s32> size = dimension2d<s32>(0,0);

	if (Image)
		size = Image->getOriginalSize();

	rect<s32> rectangle;
	rectangle.UpperLeftCorner.X = s32((AbsoluteRect.getWidth() - size.Width) / 2);
	rectangle.UpperLeftCorner.Y = s32((AbsoluteRect.getHeight() - size.Height) / 2);
	rectangle.LowerRightCorner = rectangle.UpperLeftCorner + size;

	Button->setRelativePosition(rectangle);
}

void SSGUISatelliteInfoWindow::setImage(const char *image)
{
	IVideoDriver *driver = Environment->getVideoDriver();

	if (Image)
		Image->drop();

	ITexture *oldImage = Image;

	if (image)
	{
		Image = driver->getTexture(image);
	}
	else
		Image = 0;

	if (Image)
		Image->grab();

	if (oldImage)
		driver->removeTexture(oldImage);

	update();

}

void SSGUISatelliteInfoWindow::setShowTime(u32 time)
{
	ShowTime = time;
	if (ShowTime == 0)
		ShowTime = 1000;
}

void SSGUISatelliteInfoWindow::show(const char *image)
{
	setImage(image);

	Show = true;
	this->setVisible(true);
}

void SSGUISatelliteInfoWindow::hide()
{
	Show = false;
	Button->setVisible(false);
}

bool SSGUISatelliteInfoWindow::OnEvent(const SEvent &event)
{
	if (event.GUIEvent.EventType == EGET_BUTTON_CLICKED && event.GUIEvent.Caller == Button)
	{
		hide();
		return true;
	}

	return IGUIElement::OnEvent(event);
}

void SSGUISatelliteInfoWindow::OnPostRender(u32 timeMs)
{
	static u32 lastTime = timeMs;
	static bool animate = true;
	static bool currShow = Show;

	if (currShow != Show && !animate)
		animate = true;

	if (animate)
	{
		if (Show)
		{
			if (Alpha < 255)
			{
				Alpha += s32(((f32)255 / ShowTime) * (timeMs - lastTime));
			}

			if (Alpha >= 255)
			{
				Alpha = 255;
				animate = false;
				Button->setVisible(true);
				currShow = Show;
			}
		}

		else
		{
			if (Alpha > 0)
				Alpha -= s32(((f32)255 / ShowTime) * (timeMs - lastTime));

			if (Alpha <= 0)
			{
				Alpha = 0;
				animate = false;
				this->setVisible(false);
				setImage(0);
				currShow = Show;
			}
		}
	}

	lastTime = timeMs;
}

void SSGUISatelliteInfoWindow::draw()
{
	IVideoDriver *driver = Environment->getVideoDriver();

	if (IsVisible && Image)
	{
		driver->draw2DRectangle(SColor(Alpha,0,0,0), Button->getAbsolutePosition());
		driver->draw2DImage(Image, Button->getAbsolutePosition().UpperLeftCorner, rect<s32>(position2d<s32>(0,0), Image->getOriginalSize()), 0, SColor(Alpha,255,255,255), true);
	}

	IGUIElement::draw();
}