#include "SSGUISideInfoBar.h"

SSGUISideInfoBar::SSGUISideInfoBar(IGUIEnvironment *environment, IGUIElement *parent)
				: IGUIElement(EGUIET_ELEMENT, environment, parent, -1, rect<s32>(0,0,0,0))
{
	TitleBox.Background = 0;
	TitleBox.Image.Image = 0;
	TitleBox.Image.Rect = rect<s32>(0,0,0,0);
	TitleBox.Color = SColor(255,255,255,255);
	TitleBox.Rect = rect<s32>(0,0,0,0);

	ImageBox.Background = 0;
	ImageBox.Image.Image = 0;
	ImageBox.Image.Rect = rect<s32>(0,0,0,0);
	ImageBox.Color = SColor(255,255,255,255);
	ImageBox.Rect = rect<s32>(0,0,0,0);

	GInfoBox.Background = 0;
	GInfoBox.Image.Image = 0;
	GInfoBox.Image.Rect = rect<s32>(0,0,0,0);
	GInfoBox.Color = SColor(255,255,255,255);
	GInfoBox.Rect = rect<s32>(0,0,0,0);

	PHInfoBox.Background = 0;
	PHInfoBox.Image.Image = 0;
	PHInfoBox.Image.Rect = rect<s32>(0,0,0,0);
	PHInfoBox.Color = SColor(255,255,255,255);
	PHInfoBox.Rect = rect<s32>(0,0,0,0);

	Displacement.GInfoBox = 0;
	Displacement.ImageBox = 0;
	Displacement.PHInfoBox = 0;
	Displacement.TitleBox = 0;

	IntervalBetweenBoxes = 0;
	HIndention = 0;
	VIndention = 0;

	Visible = true;

	neededState = 0;
	animSpeed = 3.0f;
	Alpha = 0;
}

SSGUISideInfoBar::~SSGUISideInfoBar()
{
	if (TitleBox.Background)
		TitleBox.Background->drop();
	if (TitleBox.Image.Image)
		TitleBox.Image.Image->drop();
	if (ImageBox.Background)
		ImageBox.Background->drop();
	if (ImageBox.Image.Image)
		ImageBox.Image.Image->drop();
	if (GInfoBox.Background)
		GInfoBox.Background->drop();
	if (GInfoBox.Image.Image)
		GInfoBox.Image.Image->drop();
	if (PHInfoBox.Background)
		PHInfoBox.Background->drop();
	if (PHInfoBox.Image.Image)
		PHInfoBox.Image.Image->drop();
}

void SSGUISideInfoBar::update()
{
	s32 Width = 0;
	s32 sumHeight = 0;

	if (TitleBox.Background)
	{
		Width = TitleBox.Background->getSize().Width;
		sumHeight += TitleBox.Background->getSize().Height;
	}
	if (ImageBox.Background)
	{
		if (ImageBox.Background->getSize().Width > Width)
			Width = ImageBox.Background->getSize().Width;
		sumHeight += ImageBox.Background->getSize().Height;
	}
	if (GInfoBox.Background)
	{
		if (GInfoBox.Background->getSize().Width > Width)
			Width = GInfoBox.Background->getSize().Width;
		sumHeight += GInfoBox.Background->getSize().Height;
	}
	if (PHInfoBox.Background)
	{
		if (PHInfoBox.Background->getSize().Width > Width)
			Width = PHInfoBox.Background->getSize().Width;
		sumHeight += PHInfoBox.Background->getSize().Height;
	}

	dimension2d<s32> screenSize = Environment->getVideoDriver()->getScreenSize();
	IGUIElement::setRelativePosition(
		rect<s32>(screenSize.Width - HIndention - Width, VIndention,
		screenSize.Width - HIndention, screenSize.Height - VIndention));

	IntervalBetweenBoxes = s32((IGUIElement::getAbsolutePosition().getHeight() - sumHeight) / 3);
}

void SSGUISideInfoBar::rebuild()
{
	update();

	s32 X = IGUIElement::getAbsolutePosition().UpperLeftCorner.X;
	s32 Y = IGUIElement::getAbsolutePosition().UpperLeftCorner.Y;
	s32 Width = IGUIElement::getAbsolutePosition().getWidth();
	s32 Height = IGUIElement::getAbsolutePosition().getHeight();

	if (TitleBox.Background)
	{
		TitleBox.Rect.UpperLeftCorner.X = X + s32((Width - TitleBox.Background->getSize().Width) / 2) + Displacement.TitleBox;
		TitleBox.Rect.UpperLeftCorner.Y = Y;
		TitleBox.Rect.LowerRightCorner.X = TitleBox.Rect.UpperLeftCorner.X + TitleBox.Background->getSize().Width;
		TitleBox.Rect.LowerRightCorner.Y = TitleBox.Rect.UpperLeftCorner.Y + TitleBox.Background->getSize().Height;

		if (TitleBox.Image.Image)
		{
			TitleBox.Image.Rect.UpperLeftCorner.X = TitleBox.Rect.UpperLeftCorner.X + s32((TitleBox.Rect.getWidth() - TitleBox.Image.Image->getSize().Width) / 2);
			TitleBox.Image.Rect.UpperLeftCorner.Y = TitleBox.Rect.UpperLeftCorner.Y + s32((TitleBox.Rect.getHeight() - TitleBox.Image.Image->getSize().Height) / 2);
			TitleBox.Image.Rect.LowerRightCorner = TitleBox.Image.Rect.UpperLeftCorner + TitleBox.Image.Image->getSize();
		}

		Y += TitleBox.Background->getSize().Height + IntervalBetweenBoxes;
	}

	if (ImageBox.Background)
	{
		ImageBox.Rect.UpperLeftCorner.X = X + s32((Width - ImageBox.Background->getSize().Width) / 2) + Displacement.ImageBox;
		ImageBox.Rect.UpperLeftCorner.Y = Y;
		ImageBox.Rect.LowerRightCorner.X = ImageBox.Rect.UpperLeftCorner.X + ImageBox.Background->getSize().Width;
		ImageBox.Rect.LowerRightCorner.Y = ImageBox.Rect.UpperLeftCorner.Y + ImageBox.Background->getSize().Height;

		if (ImageBox.Image.Image)
		{
			ImageBox.Image.Rect.UpperLeftCorner.X = ImageBox.Rect.UpperLeftCorner.X + s32((ImageBox.Rect.getWidth() - ImageBox.Image.Image->getSize().Width) / 2);
			ImageBox.Image.Rect.UpperLeftCorner.Y = ImageBox.Rect.UpperLeftCorner.Y + s32((ImageBox.Rect.getHeight() - ImageBox.Image.Image->getSize().Height) / 2);
			ImageBox.Image.Rect.LowerRightCorner = ImageBox.Image.Rect.UpperLeftCorner + ImageBox.Image.Image->getSize();
		}

		Y += ImageBox.Background->getSize().Height + IntervalBetweenBoxes;
	}

	if (GInfoBox.Background)
	{
		GInfoBox.Rect.UpperLeftCorner.X = X + s32((Width - GInfoBox.Background->getSize().Width) / 2) + Displacement.GInfoBox;
		GInfoBox.Rect.UpperLeftCorner.Y = Y;
		GInfoBox.Rect.LowerRightCorner.X = GInfoBox.Rect.UpperLeftCorner.X + GInfoBox.Background->getSize().Width;
		GInfoBox.Rect.LowerRightCorner.Y = GInfoBox.Rect.UpperLeftCorner.Y + GInfoBox.Background->getSize().Height;

		if (GInfoBox.Image.Image)
		{
			GInfoBox.Image.Rect.UpperLeftCorner.X = GInfoBox.Rect.UpperLeftCorner.X + s32((GInfoBox.Rect.getWidth() - GInfoBox.Image.Image->getSize().Width) / 2);
			GInfoBox.Image.Rect.UpperLeftCorner.Y = GInfoBox.Rect.UpperLeftCorner.Y + s32((GInfoBox.Rect.getHeight() - GInfoBox.Image.Image->getSize().Height) / 2);
			GInfoBox.Image.Rect.LowerRightCorner = GInfoBox.Rect.UpperLeftCorner + GInfoBox.Image.Image->getSize();
		}

		Y += GInfoBox.Background->getSize().Height + IntervalBetweenBoxes;
	}

	if (PHInfoBox.Background)
	{
		PHInfoBox.Rect.UpperLeftCorner.X = X + s32((Width - PHInfoBox.Background->getSize().Width) / 2) + Displacement.PHInfoBox;
		PHInfoBox.Rect.UpperLeftCorner.Y = Y;
		PHInfoBox.Rect.LowerRightCorner.X = PHInfoBox.Rect.UpperLeftCorner.X + PHInfoBox.Background->getSize().Width;
		PHInfoBox.Rect.LowerRightCorner.Y = PHInfoBox.Rect.UpperLeftCorner.Y + PHInfoBox.Background->getSize().Height;

		if (PHInfoBox.Image.Image)
		{
			PHInfoBox.Image.Rect.UpperLeftCorner.X = PHInfoBox.Rect.UpperLeftCorner.X + s32((PHInfoBox.Rect.getWidth() - PHInfoBox.Image.Image->getSize().Width) / 2);
			PHInfoBox.Image.Rect.UpperLeftCorner.Y = PHInfoBox.Rect.UpperLeftCorner.Y + s32((PHInfoBox.Rect.getHeight() - PHInfoBox.Image.Image->getSize().Height) / 2);
			PHInfoBox.Image.Rect.LowerRightCorner = PHInfoBox.Image.Rect.UpperLeftCorner + PHInfoBox.Image.Image->getSize();
		}
	}
}

void SSGUISideInfoBar::setHIndention(s32 HIndention)
{
	SSGUISideInfoBar::HIndention = HIndention;

	rebuild();
}

void SSGUISideInfoBar::setVIndention(s32 VIndention)
{
	SSGUISideInfoBar::VIndention = VIndention;

	rebuild();
}

void SSGUISideInfoBar::setBackground(ITexture *titleBoxBackground, ITexture *imageBoxBackground, ITexture *ginfoBoxBackground, ITexture *phinfoBoxBackground)
{
	TitleBox.Background = titleBoxBackground;
	ImageBox.Background = imageBoxBackground;
	GInfoBox.Background = ginfoBoxBackground;
	PHInfoBox.Background = phinfoBoxBackground;

	rebuild();
}

void SSGUISideInfoBar::setTitleBox(ITexture *image, SColor color)
{
	if (TitleBox.Image.Image)
		TitleBox.Image.Image->drop();

	TitleBox.Image.Image = image;

	if (TitleBox.Image.Image)
		TitleBox.Image.Image->grab();

	TitleBox.Color = color;

	rebuild();
}

ITexture* SSGUISideInfoBar::getTitleBox()
{
	return TitleBox.Image.Image;
}

void SSGUISideInfoBar::setImageBox(ITexture *image, SColor color)
{
	if (ImageBox.Image.Image)
		ImageBox.Image.Image->drop();

	ImageBox.Image.Image = image;

	if (ImageBox.Image.Image)
		ImageBox.Image.Image->grab();

	ImageBox.Color = color;

	rebuild();
}

ITexture* SSGUISideInfoBar::getImageBox()
{
	return ImageBox.Image.Image;
}

void SSGUISideInfoBar::setGInfoBox(ITexture *image, SColor color)
{
	if (GInfoBox.Image.Image)
		GInfoBox.Image.Image->drop();

	GInfoBox.Image.Image = image;

	if (GInfoBox.Image.Image)
		GInfoBox.Image.Image->grab();

	GInfoBox.Color = color;

	rebuild();
}

ITexture* SSGUISideInfoBar::getGInfoBox()
{
	return GInfoBox.Image.Image;
}

void SSGUISideInfoBar::setPHInfoBox(ITexture *image, SColor color)
{
	if (PHInfoBox.Image.Image)
		PHInfoBox.Image.Image->drop();

	PHInfoBox.Image.Image = image;

	if (PHInfoBox.Image.Image)
		PHInfoBox.Image.Image->grab();

	PHInfoBox.Color = color;

	rebuild();
}

ITexture* SSGUISideInfoBar::getPHInfoBox()
{
	return PHInfoBox.Image.Image;
}

void SSGUISideInfoBar::show()
{
	neededState = 1;
}

void SSGUISideInfoBar::showX()
{
	Displacement.GInfoBox = 0;
	Displacement.ImageBox = 0;
	Displacement.PHInfoBox = 0;
	Displacement.TitleBox = 0;
	neededState = 1;
	rebuild();
}

void SSGUISideInfoBar::hide()
{
	neededState = 0;
}

void SSGUISideInfoBar::hideX()
{
	dimension2d<s32> screenSize = Environment->getVideoDriver()->getScreenSize();
	Displacement.TitleBox = screenSize.Width - IGUIElement::getAbsolutePosition().UpperLeftCorner.X + s32((IGUIElement::getAbsolutePosition().getWidth() - TitleBox.Rect.getWidth()) / 2);
	Displacement.ImageBox = screenSize.Width - IGUIElement::getAbsolutePosition().UpperLeftCorner.X + s32((IGUIElement::getAbsolutePosition().getWidth() - ImageBox.Rect.getWidth()) / 2);
	Displacement.PHInfoBox = screenSize.Width - IGUIElement::getAbsolutePosition().UpperLeftCorner.X + s32((IGUIElement::getAbsolutePosition().getWidth() - PHInfoBox.Rect.getWidth()) / 2);
	Displacement.GInfoBox = screenSize.Width - IGUIElement::getAbsolutePosition().UpperLeftCorner.X + s32((IGUIElement::getAbsolutePosition().getWidth() - GInfoBox.Rect.getWidth()) / 2);
	neededState = 0;
	rebuild();
}

void SSGUISideInfoBar::setAnimationSpeed(f32 speed)
{
	animSpeed = speed;
}

void SSGUISideInfoBar::setVisible(bool visible)
{
	Visible = visible;
}

bool SSGUISideInfoBar::isVisible() const
{
	return Visible;
}

void SSGUISideInfoBar::OnPostRender(u32 timeMs)
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
		IGUIElement::setVisible(false);

		if (neededState == 0)
		{
			if (Alpha > 0)
			{
				s32 alpha = Alpha - s32((100.0 / 255) * (timeMs - prevTime));
				if (alpha < 0)
					Alpha = 0;
				else
					Alpha = alpha;
			}

			if (PHInfoBox.Rect.UpperLeftCorner.X < screenSize.Width && Alpha == 0)
			{
				s32 Width = PHInfoBox.Rect.getWidth();
				Displacement.PHInfoBox += s32((100.0 / Width) * (timeMs - prevTime) * speed);
			}
			else if (PHInfoBox.Rect.UpperLeftCorner.X > screenSize.Width)
			{
				Displacement.PHInfoBox = screenSize.Width - IGUIElement::getAbsolutePosition().UpperLeftCorner.X + s32((IGUIElement::getAbsolutePosition().getWidth() - PHInfoBox.Rect.getWidth()) / 2);
			}

			if (GInfoBox.Rect.UpperLeftCorner.X < screenSize.Width && PHInfoBox.Rect.UpperLeftCorner.X > IGUIElement::getAbsolutePosition().UpperLeftCorner.X + s32((IGUIElement::getAbsolutePosition().getWidth() + HIndention) / 2))
			{
				s32 Width = GInfoBox.Rect.getWidth();
				Displacement.GInfoBox += s32((100.0 / Width) * (timeMs - prevTime) * speed);
			}
			else if (GInfoBox.Rect.UpperLeftCorner.X > screenSize.Width)
			{
				Displacement.GInfoBox = screenSize.Width - IGUIElement::getAbsolutePosition().UpperLeftCorner.X + s32((IGUIElement::getAbsolutePosition().getWidth() - GInfoBox.Rect.getWidth()) / 2);
			}

			if (ImageBox.Rect.UpperLeftCorner.X < screenSize.Width && GInfoBox.Rect.UpperLeftCorner.X > IGUIElement::getAbsolutePosition().UpperLeftCorner.X + s32((IGUIElement::getAbsolutePosition().getWidth() + HIndention) / 2))
			{
				s32 Width = ImageBox.Rect.getWidth();
				Displacement.ImageBox += s32((100.0 / Width) * (timeMs - prevTime) * speed);
			}
			else if (ImageBox.Rect.UpperLeftCorner.X > screenSize.Width)
			{
				Displacement.ImageBox = screenSize.Width - IGUIElement::getAbsolutePosition().UpperLeftCorner.X + s32((IGUIElement::getAbsolutePosition().getWidth() - ImageBox.Rect.getWidth()) / 2);
			}

			if (TitleBox.Rect.UpperLeftCorner.X < screenSize.Width && ImageBox.Rect.UpperLeftCorner.X > IGUIElement::getAbsolutePosition().UpperLeftCorner.X + s32((IGUIElement::getAbsolutePosition().getWidth() + HIndention) / 2))
			{
				s32 Width = TitleBox.Rect.getWidth();
				Displacement.TitleBox += s32((100.0 / Width) * (timeMs - prevTime) * speed);
			}
			else if (TitleBox.Rect.UpperLeftCorner.X > screenSize.Width)
			{
				Displacement.TitleBox = screenSize.Width - IGUIElement::getAbsolutePosition().UpperLeftCorner.X + s32((IGUIElement::getAbsolutePosition().getWidth() - TitleBox.Rect.getWidth()) / 2);
				animate = false;
			}
		}
		else if (neededState == 1)
		{
			if (TitleBox.Rect.UpperLeftCorner.X > IGUIElement::getAbsolutePosition().UpperLeftCorner.X + s32((IGUIElement::getAbsolutePosition().getWidth() - TitleBox.Rect.getWidth()) / 2))
			{
				s32 Width = TitleBox.Rect.getWidth();
				Displacement.TitleBox -= s32((100.0 / Width) * (timeMs - prevTime) * speed);
			}
			else
			{
				Displacement.TitleBox = 0;
			}

			if (ImageBox.Rect.UpperLeftCorner.X > IGUIElement::getAbsolutePosition().UpperLeftCorner.X + s32((IGUIElement::getAbsolutePosition().getWidth() - ImageBox.Rect.getWidth()) / 2)
				&& TitleBox.Rect.UpperLeftCorner.X < IGUIElement::getAbsolutePosition().UpperLeftCorner.X + s32((IGUIElement::getAbsolutePosition().getWidth() + HIndention) / 2))
			{
				s32 Width = ImageBox.Rect.getWidth();
				Displacement.ImageBox -= s32((100.0 / Width) * (timeMs - prevTime) * speed);
			}
			else if (ImageBox.Rect.UpperLeftCorner.X < IGUIElement::getAbsolutePosition().UpperLeftCorner.X + s32((IGUIElement::getAbsolutePosition().getWidth() - ImageBox.Rect.getWidth()) / 2))
			{
				Displacement.ImageBox = 0;
			}

			if (GInfoBox.Rect.UpperLeftCorner.X > IGUIElement::getAbsolutePosition().UpperLeftCorner.X + s32((IGUIElement::getAbsolutePosition().getWidth() - GInfoBox.Rect.getWidth()) / 2)
				&& ImageBox.Rect.UpperLeftCorner.X < IGUIElement::getAbsolutePosition().UpperLeftCorner.X + s32((IGUIElement::getAbsolutePosition().getWidth() + HIndention) / 2))
			{
				s32 Width = GInfoBox.Rect.getWidth();
				Displacement.GInfoBox -= s32((100.0 / Width) * (timeMs - prevTime) * speed);
			}
			else if (GInfoBox.Rect.UpperLeftCorner.X < IGUIElement::getAbsolutePosition().UpperLeftCorner.X + s32((IGUIElement::getAbsolutePosition().getWidth() - GInfoBox.Rect.getWidth()) / 2))
			{
				Displacement.GInfoBox = 0;
			}

			if (PHInfoBox.Rect.UpperLeftCorner.X > IGUIElement::getAbsolutePosition().UpperLeftCorner.X + s32((IGUIElement::getAbsolutePosition().getWidth() - PHInfoBox.Rect.getWidth()) / 2)
				&& GInfoBox.Rect.UpperLeftCorner.X < IGUIElement::getAbsolutePosition().UpperLeftCorner.X + s32((IGUIElement::getAbsolutePosition().getWidth() + HIndention) / 2))
			{
				s32 Width = PHInfoBox.Rect.getWidth();
				Displacement.PHInfoBox -= s32((100.0 / Width) * (timeMs - prevTime) * speed);
			}
			else if (PHInfoBox.Rect.UpperLeftCorner.X < IGUIElement::getAbsolutePosition().UpperLeftCorner.X + s32((IGUIElement::getAbsolutePosition().getWidth() - PHInfoBox.Rect.getWidth()) / 2))
			{
				Displacement.PHInfoBox = 0;
			}

			if (Alpha < 255 && Displacement.PHInfoBox == 0)
			{
				s32 alpha = Alpha + s32((100.0 / 255) * (timeMs - prevTime));
				if (alpha >= 255)
				{
					Alpha = 255;
					animate = false;
				}
				else
					Alpha = alpha;
			}
		}
		else
		{
			neededState = 0;
		}

		rebuild();

	}
	else if (!animate && neededState == 1)
		IGUIElement::setVisible(true);

	prevTime = timeMs;
}

void SSGUISideInfoBar::draw()
{
	if (!Visible)
		return;

	IVideoDriver *driver = Environment->getVideoDriver();
	SColor color = SColor(Alpha,255,255,255);

	if (TitleBox.Background)
	{
		driver->draw2DImage(TitleBox.Background, TitleBox.Rect.UpperLeftCorner, rect<s32>(position2d<s32>(0,0), TitleBox.Background->getOriginalSize()), 0, SColor(255,255,255,255), true);

		if (TitleBox.Image.Image)
		{
			TitleBox.Color.setAlpha(Alpha);
			driver->draw2DImage(TitleBox.Image.Image, TitleBox.Image.Rect.UpperLeftCorner, rect<s32>(position2d<s32>(0,0), TitleBox.Image.Image->getOriginalSize()), 0, TitleBox.Color, true);
		}
	}

	if (ImageBox.Background && driver->getScreenSize().Width - Displacement.ImageBox >= IGUIElement::getAbsolutePosition().UpperLeftCorner.X)
	{
		driver->draw2DImage(ImageBox.Background, ImageBox.Rect.UpperLeftCorner, rect<s32>(position2d<s32>(0,0), ImageBox.Background->getOriginalSize()), 0, SColor(255,255,255,255), true);

		if (ImageBox.Image.Image)
		{
			ImageBox.Color.setAlpha(Alpha);
			driver->draw2DImage(ImageBox.Image.Image, ImageBox.Image.Rect.UpperLeftCorner, rect<s32>(position2d<s32>(0,0), ImageBox.Image.Image->getOriginalSize()), 0, ImageBox.Color, true);
		}
	}

	if (GInfoBox.Background && driver->getScreenSize().Width - Displacement.GInfoBox >= IGUIElement::getAbsolutePosition().UpperLeftCorner.X)
	{
		driver->draw2DImage(GInfoBox.Background, GInfoBox.Rect.UpperLeftCorner, rect<s32>(position2d<s32>(0,0), GInfoBox.Background->getOriginalSize()), 0, SColor(255,255,255,255), true);
		
		if (GInfoBox.Image.Image)
		{
			GInfoBox.Color.setAlpha(Alpha);
			driver->draw2DImage(GInfoBox.Image.Image, GInfoBox.Image.Rect.UpperLeftCorner, rect<s32>(position2d<s32>(0,0), GInfoBox.Image.Image->getOriginalSize()), 0, GInfoBox.Color, true);
		}
	}

	if (PHInfoBox.Background && driver->getScreenSize().Width - Displacement.PHInfoBox >= IGUIElement::getAbsolutePosition().UpperLeftCorner.X)
	{
		driver->draw2DImage(PHInfoBox.Background, PHInfoBox.Rect.UpperLeftCorner, rect<s32>(position2d<s32>(0,0), PHInfoBox.Background->getOriginalSize()), 0, SColor(255,255,255,255), true);

		if (PHInfoBox.Image.Image)
		{
			PHInfoBox.Color.setAlpha(Alpha);
			driver->draw2DImage(PHInfoBox.Image.Image, PHInfoBox.Image.Rect.UpperLeftCorner, rect<s32>(position2d<s32>(0,0), PHInfoBox.Image.Image->getOriginalSize()), 0, PHInfoBox.Color, true);
		}
	}

	IGUIElement::draw();
}

bool SSGUISideInfoBar::OnEvent(const SEvent &event)
{
	return IGUIElement::OnEvent(event);
}