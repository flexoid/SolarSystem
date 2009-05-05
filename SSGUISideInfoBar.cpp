#include "SSGUISideInfoBar.h"

SSGUISideInfoBar::SSGUISideInfoBar(IGUIEnvironment *environment, IGUIElement *parent)
				: IGUIElement(EGUIET_ELEMENT, environment, parent, -1, rect<s32>(0,0,0,0))
{
	TitleBox.Background = 0;
	TitleBox.Caption.Color = SColor(255,255,255,255);
	TitleBox.Caption.Font = Environment->getSkin()->getFont();
	TitleBox.Caption.HCener = false;
	TitleBox.Caption.Rect = rect<s32>(0,0,0,0);
	TitleBox.Caption.Text = 0;
	TitleBox.Caption.VCenter = false;
	TitleBox.Rect = rect<s32>(0,0,0,0);

	ImageBox.Background = 0;
	ImageBox.Icon.HCenter = false;
	ImageBox.Icon.Image = 0;
	ImageBox.Icon.Rect = rect<s32>(0,0,0,0);
	ImageBox.Icon.VCenter = false;
	ImageBox.Image.HCenter = false;
	ImageBox.Image.Image = 0;
	ImageBox.Image.Rect = rect<s32>(0,0,0,0);
	ImageBox.Image.VCenter = false;
	ImageBox.ImageBackground.HCenter = false;
	ImageBox.ImageBackground.Image = 0;
	ImageBox.ImageBackground.Rect = rect<s32>(0,0,0,0);
	ImageBox.ImageBackground.VCenter = false;
	ImageBox.Rect = rect<s32>(0,0,0,0);

	PHInfoBox.Background = 0;
	PHInfoBox.TextBox.HIndention = 0;
	PHInfoBox.TextBox.IntervalBetweenLines = 0;
	PHInfoBox.TextBox.VIndention = 0;
	PHInfoBox.TextBox.Rect = rect<s32>(0,0,0,0);
	PHInfoBox.TextBox.Font = 0;
	PHInfoBox.TextBox.ColorLeft = SColor(255,255,255,255);
	PHInfoBox.TextBox.ColorRight = SColor(255,255,255,255);
	PHInfoBox.Rect = rect<s32>(0,0,0,0);

	GInfoBox.Background = 0;
	GInfoBox.Text = Environment->addStaticText(0, rect<s32>(0,0,0,0));
	GInfoBox.Rect = rect<s32>(0,0,0,0);

	Displacement.GInfoBox = 0;
	Displacement.ImageBox = 0;
	Displacement.PHInfoBox = 0;
	Displacement.TitleBox = 0;

	IntervalBetweenBoxes = 0;
	HIndention = 0;
	VIndention = 0;

	neededState = 0;
	animSpeed = 3.0f;
	Alpha = 0;
}

SSGUISideInfoBar::~SSGUISideInfoBar()
{
	if (TitleBox.Background)
		TitleBox.Background->drop();
	if (ImageBox.Background)
		ImageBox.Background->drop();
	if (ImageBox.Icon.Image)
		ImageBox.Icon.Image->drop();
	if (ImageBox.Image.Image)
		ImageBox.Image.Image->drop();
	if (PHInfoBox.Background)
		PHInfoBox.Background->drop();
	if (GInfoBox.Background)
		GInfoBox.Background->drop();
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
	if (PHInfoBox.Background)
	{
		if (PHInfoBox.Background->getSize().Width > Width)
			Width = PHInfoBox.Background->getSize().Width;
		sumHeight += PHInfoBox.Background->getSize().Height;
	}
	if (GInfoBox.Background)
	{
		if (GInfoBox.Background->getSize().Width > Width)
			Width = GInfoBox.Background->getSize().Width;
		sumHeight += GInfoBox.Background->getSize().Height;
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

		TitleBox.Caption.Rect = TitleBox.Rect;
		if (!TitleBox.Caption.Font)
			TitleBox.Caption.Font = Environment->getSkin()->getFont();

		Y += TitleBox.Background->getSize().Height + IntervalBetweenBoxes;
	}

	if (ImageBox.Background)
	{
		ImageBox.Rect.UpperLeftCorner.X = X + s32((Width - ImageBox.Background->getSize().Width) / 2) + Displacement.ImageBox;
		ImageBox.Rect.UpperLeftCorner.Y = Y;
		ImageBox.Rect.LowerRightCorner.X = ImageBox.Rect.UpperLeftCorner.X + ImageBox.Background->getSize().Width;
		ImageBox.Rect.LowerRightCorner.Y = ImageBox.Rect.UpperLeftCorner.Y + ImageBox.Background->getSize().Height;

		if (ImageBox.ImageBackground.Image)
		{
			ImageBox.ImageBackground.Rect.UpperLeftCorner.X = X + s32((ImageBox.Rect.getWidth() - ImageBox.ImageBackground.Image->getSize().Width) / 2) + Displacement.ImageBox;
			ImageBox.ImageBackground.Rect.UpperLeftCorner.Y = Y + s32((ImageBox.Rect.getHeight() - ImageBox.ImageBackground.Image->getSize().Height) / 2);
			ImageBox.ImageBackground.Rect.LowerRightCorner.X = ImageBox.ImageBackground.Rect.UpperLeftCorner.X + ImageBox.ImageBackground.Image->getSize().Width;
			ImageBox.ImageBackground.Rect.LowerRightCorner.Y = ImageBox.ImageBackground.Rect.UpperLeftCorner.Y + ImageBox.ImageBackground.Image->getSize().Height;

			if (ImageBox.Image.Image)
			{
				ImageBox.Image.Rect.UpperLeftCorner.X = ImageBox.ImageBackground.Rect.UpperLeftCorner.X + s32((ImageBox.ImageBackground.Rect.getWidth() - ImageBox.Image.Image->getSize().Width) / 2);
				ImageBox.Image.Rect.UpperLeftCorner.Y = ImageBox.ImageBackground.Rect.UpperLeftCorner.Y + s32((ImageBox.ImageBackground.Rect.getHeight() - ImageBox.Image.Image->getSize().Height) / 2);
				ImageBox.Image.Rect.LowerRightCorner.X = ImageBox.Image.Rect.UpperLeftCorner.X + ImageBox.Image.Image->getSize().Width;
				ImageBox.Image.Rect.LowerRightCorner.Y = ImageBox.Image.Rect.UpperLeftCorner.Y + ImageBox.Image.Image->getSize().Height;

				if (ImageBox.Icon.Image)
				{
					ImageBox.Icon.Rect.UpperLeftCorner.X = ImageBox.ImageBackground.Rect.LowerRightCorner.X - ImageBox.Icon.Image->getSize().Width - s32(ImageBox.ImageBackground.Rect.getWidth() * 0.03f);
					ImageBox.Icon.Rect.UpperLeftCorner.Y = ImageBox.ImageBackground.Rect.LowerRightCorner.Y - ImageBox.Icon.Image->getSize().Height - s32(ImageBox.ImageBackground.Rect.getWidth() * 0.03f);
					ImageBox.Icon.Rect.LowerRightCorner.X = ImageBox.Icon.Rect.UpperLeftCorner.X + ImageBox.Icon.Rect.getWidth();
					ImageBox.Icon.Rect.LowerRightCorner.Y = ImageBox.Icon.Rect.UpperLeftCorner.Y + ImageBox.Icon.Rect.getHeight();
				}
			}
		}

		Y += ImageBox.Background->getSize().Height + IntervalBetweenBoxes;

		if (PHInfoBox.Background)
		{
			PHInfoBox.Rect.UpperLeftCorner.X = X + s32((Width - PHInfoBox.Background->getSize().Width) / 2) + Displacement.PHInfoBox;
			PHInfoBox.Rect.UpperLeftCorner.Y = Y;
			PHInfoBox.Rect.LowerRightCorner.X = PHInfoBox.Rect.UpperLeftCorner.X + PHInfoBox.Background->getSize().Width;
			PHInfoBox.Rect.LowerRightCorner.Y = PHInfoBox.Rect.UpperLeftCorner.Y + PHInfoBox.Background->getSize().Height;

			if (PHInfoBox.TextBox.TextBox.size() > 0)
			{
				PHInfoBox.TextBox.Rect.UpperLeftCorner.X = PHInfoBox.Rect.UpperLeftCorner.X + PHInfoBox.TextBox.HIndention;
				PHInfoBox.TextBox.Rect.UpperLeftCorner.Y = PHInfoBox.Rect.UpperLeftCorner.Y + PHInfoBox.TextBox.VIndention;
				PHInfoBox.TextBox.Rect.LowerRightCorner.X = PHInfoBox.Rect.LowerRightCorner.X - PHInfoBox.TextBox.HIndention;
				PHInfoBox.TextBox.Rect.LowerRightCorner.Y = PHInfoBox.Rect.LowerRightCorner.Y - PHInfoBox.TextBox.VIndention;

				if (!PHInfoBox.TextBox.Font)
					PHInfoBox.TextBox.Font = Environment->getSkin()->getFont();

				PHInfoBox.TextBox.IntervalBetweenLines = s32(PHInfoBox.TextBox.Font->getDimension(L"A").Height * 0.25);

				s32 PHY = 0;
				for (s32 i = 0; i < (s32)PHInfoBox.TextBox.TextBox.size(); i++)
				{
					rect<s32> rectangle = rect<s32>(0,0,0,0);
					rectangle.UpperLeftCorner.X = PHInfoBox.TextBox.Rect.UpperLeftCorner.X;
					rectangle.UpperLeftCorner.Y = PHInfoBox.TextBox.Rect.UpperLeftCorner.Y + PHY;
					rectangle.LowerRightCorner.X = PHInfoBox.TextBox.Rect.LowerRightCorner.X;
					rectangle.LowerRightCorner.Y = rectangle.UpperLeftCorner.Y + PHInfoBox.TextBox.Font->getDimension(L"A").Height;

					if (PHInfoBox.TextBox.Rect.isPointInside(rectangle.LowerRightCorner))
					{
						PHInfoBox.TextBox.TextBox[i].Rect = rectangle;

						rectangle.UpperLeftCorner.X = PHInfoBox.TextBox.TextBox[i].Rect.UpperLeftCorner.X;
						rectangle.UpperLeftCorner.Y = PHInfoBox.TextBox.TextBox[i].Rect.UpperLeftCorner.Y;
						rectangle.LowerRightCorner.X = rectangle.UpperLeftCorner.X + PHInfoBox.TextBox.Font->getDimension(PHInfoBox.TextBox.TextBox[i].Left.Text).Width;
						rectangle.LowerRightCorner.Y = PHInfoBox.TextBox.TextBox[i].Rect.LowerRightCorner.Y;
						PHInfoBox.TextBox.TextBox[i].Left.Rect = rectangle;

						rectangle.UpperLeftCorner.X = PHInfoBox.TextBox.TextBox[i].Rect.LowerRightCorner.X - PHInfoBox.TextBox.Font->getDimension(PHInfoBox.TextBox.TextBox[i].Right.Text).Width;
						rectangle.LowerRightCorner.X = PHInfoBox.TextBox.TextBox[i].Rect.LowerRightCorner.X;
						PHInfoBox.TextBox.TextBox[i].Right.Rect = rectangle;
					}
					else
					{
						break;
					}

					PHY += PHInfoBox.TextBox.TextBox[i].Rect.getHeight() + PHInfoBox.TextBox.IntervalBetweenLines;
				}
			}

			Y += PHInfoBox.Background->getSize().Height + IntervalBetweenBoxes;
		}

		if (GInfoBox.Background)
		{
			GInfoBox.Rect.UpperLeftCorner.X = X + s32((Width - GInfoBox.Background->getSize().Width) / 2) + Displacement.GInfoBox;
			GInfoBox.Rect.UpperLeftCorner.Y = Y;
			GInfoBox.Rect.LowerRightCorner.X = GInfoBox.Rect.UpperLeftCorner.X + GInfoBox.Background->getSize().Width;
			GInfoBox.Rect.LowerRightCorner.Y = GInfoBox.Rect.UpperLeftCorner.Y + GInfoBox.Background->getSize().Height;

			if (GInfoBox.Text->getText())
			{
				rect<s32> rectangle = rect<s32>(0,0,0,0);
				rectangle.UpperLeftCorner.X = GInfoBox.Rect.UpperLeftCorner.X + 20;
				rectangle.UpperLeftCorner.Y = GInfoBox.Rect.UpperLeftCorner.Y + 20;
				rectangle.LowerRightCorner.X = GInfoBox.Rect.LowerRightCorner.X - 20;
				rectangle.LowerRightCorner.Y = GInfoBox.Rect.LowerRightCorner.Y - 20;
				GInfoBox.Text->setRelativePosition(rectangle);
			}
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

void SSGUISideInfoBar::setBackground(ITexture *titleBoxBackground, ITexture *imageBoxBackground, ITexture *phinfoBoxBackground, ITexture *ginfoBoxBackground)
{
	TitleBox.Background = titleBoxBackground;
	ImageBox.Background = imageBoxBackground;
	PHInfoBox.Background = phinfoBoxBackground;
	GInfoBox.Background = ginfoBoxBackground;

	rebuild();
}

void SSGUISideInfoBar::setTitleBoxCaption(const wchar_t *text, IGUIFont *font, SColor color)
{
	TitleBox.Caption.Text = text;
	if (font)
		TitleBox.Caption.Font = font;
	TitleBox.Caption.Color = color;
}

void SSGUISideInfoBar::setImageBoxIcon(ITexture *image)
{
	ImageBox.Icon.Image = image;

	rebuild();
}

void SSGUISideInfoBar::setImageBoxImage(ITexture *image)
{
	ImageBox.Image.Image = image;

	rebuild();
}

void SSGUISideInfoBar::setImageBoxImageBackground(ITexture *image)
{
	ImageBox.ImageBackground.Image = image;

	rebuild();
}

void SSGUISideInfoBar::setPHInfoBoxTextBoxAttributes(s32 HIndention, s32 VIndention, IGUIFont *font, SColor color1, SColor color2)
{
	PHInfoBox.TextBox.HIndention = HIndention;
	PHInfoBox.TextBox.VIndention = VIndention;
	PHInfoBox.TextBox.Font = font;
	PHInfoBox.TextBox.ColorLeft = color1;
	PHInfoBox.TextBox.ColorRight = color2;

	rebuild();
}

s32 SSGUISideInfoBar::addPHInfoBoxTextBlock(wchar_t *text1, wchar_t *text2, s32 id)
{
	if (id == -1)
	{
		id = PHInfoBox.TextBox.TextBox.size();
		SideInfoBarPHInfoBoxTextStructure textBlock;
		PHInfoBox.TextBox.TextBox.push_back(textBlock);
	}
	
	if (id < (s32)PHInfoBox.TextBox.TextBox.size() && id >= 0)
	{
		PHInfoBox.TextBox.TextBox[id].Left.Text = text1;
		PHInfoBox.TextBox.TextBox[id].Right.Text = text2;
	}
	else
		id = -1;

	return id;
}

void SSGUISideInfoBar::setGInfoBoxText(wchar_t *text, IGUIFont *font, SColor color)
{
	stringw string = L"      ";
	string += text;
	GInfoBox.Text->setText(string.c_str());

	GInfoBox.Text->setOverrideFont(font);

	GInfoBox.Text->setOverrideColor(color);

	rebuild();
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

			if (GInfoBox.Rect.UpperLeftCorner.X < screenSize.Width && Alpha == 0)
			{
				s32 Width = GInfoBox.Rect.getWidth();
				Displacement.GInfoBox += s32((100.0 / Width) * (timeMs - prevTime) * speed);
			}
			else if (GInfoBox.Rect.UpperLeftCorner.X > screenSize.Width)
			{
				Displacement.GInfoBox = screenSize.Width - IGUIElement::getAbsolutePosition().UpperLeftCorner.X + s32((IGUIElement::getAbsolutePosition().getWidth() - GInfoBox.Rect.getWidth()) / 2);
			}

			if (PHInfoBox.Rect.UpperLeftCorner.X < screenSize.Width && GInfoBox.Rect.UpperLeftCorner.X > IGUIElement::getAbsolutePosition().UpperLeftCorner.X + s32((IGUIElement::getAbsolutePosition().getWidth() + HIndention) / 2))
			{
				s32 Width = PHInfoBox.Rect.getWidth();
				Displacement.PHInfoBox += s32((100.0 / Width) * (timeMs - prevTime) * speed);
			}
			else if (PHInfoBox.Rect.UpperLeftCorner.X > screenSize.Width)
			{
				Displacement.PHInfoBox = screenSize.Width - IGUIElement::getAbsolutePosition().UpperLeftCorner.X + s32((IGUIElement::getAbsolutePosition().getWidth() - PHInfoBox.Rect.getWidth()) / 2);
			}

			if (ImageBox.Rect.UpperLeftCorner.X < screenSize.Width && PHInfoBox.Rect.UpperLeftCorner.X > IGUIElement::getAbsolutePosition().UpperLeftCorner.X + s32((IGUIElement::getAbsolutePosition().getWidth() + HIndention) / 2))
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

			if (PHInfoBox.Rect.UpperLeftCorner.X > IGUIElement::getAbsolutePosition().UpperLeftCorner.X + s32((IGUIElement::getAbsolutePosition().getWidth() - PHInfoBox.Rect.getWidth()) / 2)
				&& ImageBox.Rect.UpperLeftCorner.X < IGUIElement::getAbsolutePosition().UpperLeftCorner.X + s32((IGUIElement::getAbsolutePosition().getWidth() + HIndention) / 2))
			{
				s32 Width = PHInfoBox.Rect.getWidth();
				Displacement.PHInfoBox -= s32((100.0 / Width) * (timeMs - prevTime) * speed);
			}
			else if (PHInfoBox.Rect.UpperLeftCorner.X < IGUIElement::getAbsolutePosition().UpperLeftCorner.X + s32((IGUIElement::getAbsolutePosition().getWidth() - PHInfoBox.Rect.getWidth()) / 2))
			{
				Displacement.PHInfoBox = 0;
			}

			if (GInfoBox.Rect.UpperLeftCorner.X > IGUIElement::getAbsolutePosition().UpperLeftCorner.X + s32((IGUIElement::getAbsolutePosition().getWidth() - GInfoBox.Rect.getWidth()) / 2)
				&& PHInfoBox.Rect.UpperLeftCorner.X < IGUIElement::getAbsolutePosition().UpperLeftCorner.X + s32((IGUIElement::getAbsolutePosition().getWidth() + HIndention) / 2))
			{
				s32 Width = GInfoBox.Rect.getWidth();
				Displacement.GInfoBox -= s32((100.0 / Width) * (timeMs - prevTime) * speed);
			}
			else if (GInfoBox.Rect.UpperLeftCorner.X < IGUIElement::getAbsolutePosition().UpperLeftCorner.X + s32((IGUIElement::getAbsolutePosition().getWidth() - GInfoBox.Rect.getWidth()) / 2))
			{
				Displacement.GInfoBox = 0;
			}

			if (Alpha < 255 && Displacement.GInfoBox == 0)
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
	IVideoDriver *driver = Environment->getVideoDriver();
	SColor color = SColor(Alpha,255,255,255);

	if (TitleBox.Background)
	{
		driver->draw2DImage(TitleBox.Background, TitleBox.Rect.UpperLeftCorner, rect<s32>(position2d<s32>(0,0), TitleBox.Background->getOriginalSize()), 0, SColor(255,255,255,255), true);

		if (TitleBox.Caption.Text)
		{
			TitleBox.Caption.Color.setAlpha(Alpha);
			if (Alpha > 0)
				TitleBox.Caption.Font->draw(TitleBox.Caption.Text, TitleBox.Caption.Rect, TitleBox.Caption.Color, true, true);
		}
	}

	if (ImageBox.Background && driver->getScreenSize().Width - Displacement.ImageBox >= IGUIElement::getAbsolutePosition().UpperLeftCorner.X)
	{
		driver->draw2DImage(ImageBox.Background, ImageBox.Rect.UpperLeftCorner, rect<s32>(position2d<s32>(0,0), ImageBox.Background->getOriginalSize()), 0, SColor(255,255,255,255), true);

		if (ImageBox.ImageBackground.Image)
		{
			driver->draw2DImage(ImageBox.ImageBackground.Image, ImageBox.ImageBackground.Rect.UpperLeftCorner, rect<s32>(position2d<s32>(0,0), ImageBox.ImageBackground.Image->getOriginalSize()), 0, SColor(255,255,255,255), true);

			if (Alpha > 0)
			{
				if (ImageBox.Image.Image)
				{
					driver->draw2DImage(ImageBox.Image.Image, ImageBox.Image.Rect.UpperLeftCorner, rect<s32>(position2d<s32>(0,0), ImageBox.Image.Image->getOriginalSize()), 0, color, true);

					if (ImageBox.Icon.Image)
					{
						driver->draw2DImage(ImageBox.Icon.Image, ImageBox.Icon.Rect.UpperLeftCorner, rect<s32>(position2d<s32>(0,0), ImageBox.Icon.Image->getOriginalSize()), 0, TitleBox.Caption.Color, true);
					}
				}
			}
		}
	}

	if (PHInfoBox.Background && driver->getScreenSize().Width - Displacement.PHInfoBox >= IGUIElement::getAbsolutePosition().UpperLeftCorner.X)
	{
		driver->draw2DImage(PHInfoBox.Background, PHInfoBox.Rect.UpperLeftCorner, rect<s32>(position2d<s32>(0,0), PHInfoBox.Background->getOriginalSize()), 0, SColor(255,255,255,255), true);

		PHInfoBox.TextBox.ColorLeft.setAlpha(Alpha);
		PHInfoBox.TextBox.ColorRight.setAlpha(Alpha);

		if (Alpha > 0)
		{
			for (s32 i = 0; i < (s32)PHInfoBox.TextBox.TextBox.size(); i++)
			{
					PHInfoBox.TextBox.Font->draw(PHInfoBox.TextBox.TextBox[i].Left.Text, PHInfoBox.TextBox.TextBox[i].Left.Rect, PHInfoBox.TextBox.ColorLeft);
					PHInfoBox.TextBox.Font->draw(PHInfoBox.TextBox.TextBox[i].Right.Text, PHInfoBox.TextBox.TextBox[i].Right.Rect, PHInfoBox.TextBox.ColorRight);
			}
		}
	}

	if (GInfoBox.Background && driver->getScreenSize().Width - Displacement.GInfoBox >= IGUIElement::getAbsolutePosition().UpperLeftCorner.X)
	{
		driver->draw2DImage(GInfoBox.Background, GInfoBox.Rect.UpperLeftCorner, rect<s32>(position2d<s32>(0,0), GInfoBox.Background->getOriginalSize()), 0, SColor(255,255,255,255), true);
		
		color = GInfoBox.Text->getOverrideColor();
		color.setAlpha(Alpha);
		GInfoBox.Text->setOverrideColor(color);
	}

	IGUIElement::draw();
}

bool SSGUISideInfoBar::OnEvent(const SEvent &event)
{
	return IGUIElement::OnEvent(event);
}