#include "SSFreeFlightCameraMode.h"

#include <windows.h>

SSFreeFlightCameraMode::SSFreeFlightCameraMode(IGUIEnvironment *environment, ISceneManager *sceneManager, ICursorControl *cursorControl, const array<IGUIElement*> &GUIElements)
					: IGUIElement(EGUIET_ELEMENT, environment, environment->getRootGUIElement(), -1, rect<s32>(0,0,0,0)),
					SwitchONTime(1000), SwitchON(false), SwitchedON(false)
{
	SceneManager = sceneManager;
	CursorControl = cursorControl;

	for (s32 i = 0; i < (s32)GUIElements.size(); i++)
	{
		RegisteredGUIElement element = {GUIElements[i], GUIElements[i]->isVisible()};
		this->GUIElements.push_back(element);
	}

	AltCamera = SceneManager->getActiveCamera();

	FPSCamera = SceneManager->addCameraSceneNodeFPS(0, 100.0f, 500.0f);
	FPSCamera->setFarValue(9999999.0f);

	SceneManager->setActiveCamera(AltCamera);

	dimension2d<s32> size = Environment->getVideoDriver()->getScreenSize();
	IGUIElement::setRelativePosition(rect<s32>(position2d<s32>(0,0), size));
	IGUIElement::setVisible(false);

	Label.Text = 0;
	Label.Font = Environment->getSkin()->getFont();
	Label.Color = SColor(255,255,255,255);
	Label.Rect = rect<s32>(0,0,0,0);
}

SSFreeFlightCameraMode::~SSFreeFlightCameraMode()
{
}

void SSFreeFlightCameraMode::setSwitchONTime(u32 time)
{
	if (time != 0)
		SwitchONTime = time;
	else
		SwitchONTime = 1;
}

void SSFreeFlightCameraMode::setLabel(const wchar_t *text, IGUIFont *font, SColor color)
{
	Label.Text = text;

	if (!font)
		font = Environment->getSkin()->getFont();
	Label.Font = font;

	Label.Color = color;

	if (Label.Text)
	{
		dimension2d<s32> size = Label.Font->getDimension(Label.Text);
		Label.Rect.UpperLeftCorner.X = s32((AbsoluteRect.getWidth() - size.Width) / 2);
		Label.Rect.UpperLeftCorner.Y = AbsoluteRect.LowerRightCorner.Y - s32(size.Height * 1.2f);
		Label.Rect.LowerRightCorner = Label.Rect.UpperLeftCorner + size;
	}
}

void SSFreeFlightCameraMode::addCameraSceneNodeAnimators(const array<ISceneNode*> &nodes)
{
	for (s32 i = 0; i < (s32)nodes.size(); i++)
	{
		ITriangleSelector* selector = 0; 
		 if (nodes[i])
		 {
			 selector = SceneManager->createTriangleSelectorFromBoundingBox(nodes[i]);
			 nodes[i]->setTriangleSelector(selector); 
			 selector->drop(); 
		 }
		 ISceneNodeAnimator* anim = SceneManager->createCollisionResponseAnimator(selector,
			 FPSCamera, vector3df(30,50,30), vector3df(0,0,0), vector3df(0,0,0));
		 FPSCamera->addAnimator(anim);
		 anim->drop();
	}
}

void SSFreeFlightCameraMode::On()
{
	SwitchON = true;
}

void SSFreeFlightCameraMode::Off()
{
	SwitchON = false;
}

void SSFreeFlightCameraMode::OnPostRender(u32 timeMs)
{
	static u32 lastTime = timeMs;
	static s32 State = -1;
	static s32 Alpha = 0;
	static bool showLabel = false;
	static u32 labelTime = 0;

	IVideoDriver *driver = Environment->getVideoDriver();

	if (SwitchON && !SwitchedON)
	{
		if (State == 0 || State == -1)
		{
			Alpha += s32((255.0f / (SwitchONTime / 2)) * (timeMs - lastTime));

			if (Alpha >= 255)
			{
				Alpha = 255;
				State = 1;
			}
		}
		else if (State == 1)
		{
			CursorControl->setVisible(false);
			for (s32 i = 0; i < (s32)GUIElements.size(); i++)
			{
				GUIElements[i].wasVisible = GUIElements[i].Element->isVisible();
				GUIElements[i].Element->setVisible(false);
			}
			CursorControl->setPosition(s32(driver->getScreenSize().Width / 2), s32(driver->getScreenSize().Height / 2));
			SceneManager->setActiveCamera(FPSCamera);
			FPSCamera->setPosition(AltCamera->getPosition());
			FPSCamera->setTarget(AltCamera->getTarget());

			State = 2;
		}
		else if (State == 2)
		{
			Alpha -= s32((255.0f / (SwitchONTime / 2)) * (timeMs - lastTime));

			if (Alpha <= 0)
			{
				Alpha = 0;
				SwitchedON = true;
				State = -1;
			}
		}
	}

	else if (!SwitchON && SwitchedON)
	{
		if (State == 2 || State == -1)
		{
			Alpha += s32((255.0f / (SwitchONTime / 2)) * (timeMs - lastTime));

			if (Alpha >= 255)
			{
				Alpha = 255;
				State = 1;
			}
		}
		else if (State == 1)
		{
			CursorControl->setVisible(true);
			for (s32 i = 0; i < (s32)GUIElements.size(); i++)
			{
				GUIElements[i].Element->setVisible(GUIElements[i].wasVisible);
			}
			SceneManager->setActiveCamera(AltCamera);

			State = 0;
		}
		else if (State == 0)
		{
			Alpha -= s32((255.0f / (SwitchONTime / 2)) * (timeMs - lastTime));

			if (Alpha <= 0)
			{
				Alpha = 0;
				SwitchedON = false;
				State = -1;
			}
		}
	}

	if (SwitchedON && SwitchON)
	{
		labelTime += (timeMs - lastTime);

		if (labelTime > 1000)
		{
			labelTime = 0;
			showLabel = !showLabel;
		}

		if (showLabel && Label.Text)
			Label.Font->draw(Label.Text, Label.Rect, Label.Color);
	}

	if (Alpha > 0)
		driver->draw2DRectangle(SColor(Alpha,0,0,0), AbsoluteRect);

	if (SwitchedON && (GetKeyState(VK_SPACE) & 0x8000))
	{
		Off();
		labelTime = 0;
	}

	lastTime = timeMs;
}