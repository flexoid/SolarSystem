#include "SSGUIScrollBar.h"
#include "SSGUIFunctions.h"
#include "os.h"

#include <windows.h>

SSGUIScrollBar::SSGUIScrollBar(bool horizontal, IGUIEnvironment *environment, IGUIElement *parent, s32 id, bool noclip)
			:IGUIScrollBar(environment, parent, id, rect<s32>(0,0,0,0)),
			DownButton(0), Dragging(false), Horizontal(horizontal),
			DraggedBySlider(false), TrayClick(false), Pos(0), SliderX(0), SliderY(0), SliderOver(false),
			Max(100), SmallStep(1), LargeStep(5), DesiredPos(0), LastChange(0)
{
	UpButton = new SSGUIButton(environment, this, -1);
	DownButton = new SSGUIButton(environment, this, -1);

	for (s32 i = 0; i < SSSS_COUNT; i++)
		Rule[i] = 0;

	for (s32 i = 0; i < SSSSLS_COUNT; i++)
		Slider[i] = 0;

	setTabStop(true);
	setTabOrder(-1);
	setNotClipped(noclip);
}

SSGUIScrollBar::~SSGUIScrollBar()
{
	if (UpButton)
		UpButton->drop();
	if (DownButton)
		DownButton->drop();

	for (s32 i = 0; i < SSSS_COUNT; i++)
	{
		if (Rule[i]) Rule[i]->drop();
	}

	for (s32 i = 0; i < SSSSLS_COUNT; i++)
	{
		if (Slider[i]) Slider[i]->drop();
	}
}

void SSGUIScrollBar::setOrientation(bool horizontal)
{
	Horizontal = horizontal;
	refreshControls();
}

s32 SSGUIScrollBar::getPos() const
{
	return Pos;
}

void SSGUIScrollBar::setPos(s32 pos)
{
	if (pos < 0)
		Pos = 0;
	else if (pos > Max)
		Pos = Max;
	else
		Pos = pos;

	if (Horizontal)
	{
		const f32 f = f32((SliderRect.getWidth() - Slider[0]->getSize().Width)) / Max;

		SliderX = DownButton->getRelativePosition().LowerRightCorner.X + (s32)(Pos * f);
		SliderY = s32((SliderRect.getHeight() - Slider[0]->getSize().Height) / 2.0f);
	}
	else
	{
		const f32 f = f32((SliderRect.getHeight() - Slider[0]->getSize().Height)) / Max;

		SliderX = s32((SliderRect.getWidth() - Slider[0]->getSize().Width) / 2.0f);
		SliderY = DownButton->getRelativePosition().UpperLeftCorner.Y - (s32)(Pos * f) - Slider[0]->getSize().Height;
	}
}

s32 SSGUIScrollBar::getSmallStep() const
{
	return SmallStep;
}

void SSGUIScrollBar::setSmallStep(s32 step)
{
	if (step > 0)
		SmallStep = step;
	else
		SmallStep = 1;
}

s32 SSGUIScrollBar::getLargeStep() const
{
	return LargeStep;
}

void SSGUIScrollBar::setLargeStep(s32 step)
{
	if (step > 1)
		LargeStep = step;
	else
		LargeStep = 2;
}

s32 SSGUIScrollBar::getMax() const
{
	return Max;
}

void SSGUIScrollBar::setMax(s32 max)
{
	if (max > 1)
		Max = max;
	else
		Max = 1;
}

bool SSGUIScrollBar::OnEvent(const SEvent& event)
{
	if (rect<s32>(AbsoluteRect.UpperLeftCorner + position2d<s32>(SliderX, SliderY),
			AbsoluteRect.UpperLeftCorner + position2d<s32>(SliderX, SliderY) +
			position2d<s32>(Slider[0]->getSize().Width, Slider[0]->getSize().Height)).isPointInside(core::position2di(event.MouseInput.X, event.MouseInput.Y)))
	{
		SliderOver = true;
	}
	else SliderOver = false;
	switch(event.EventType)
	{
	case EET_KEY_INPUT_EVENT:
		if (event.KeyInput.PressedDown)
		{
			const s32 oldPos = Pos;
			bool absorb = true;
			switch (event.KeyInput.Key)
			{
			case KEY_LEFT:
			case KEY_UP:
				setPos(Pos+SmallStep);
				break;
			case KEY_RIGHT:
			case KEY_DOWN:
				setPos(Pos-SmallStep);
				break;
			case KEY_HOME:
				setPos(0);
				break;
			case KEY_PRIOR:
				setPos(Pos+LargeStep);
				break;
			case KEY_END:
				setPos(Max);
				break;
			case KEY_NEXT:
				setPos(Pos-LargeStep);
				break;
			default:
				absorb = false;
			}

			if (Pos != oldPos)
			{
				SEvent newEvent;
				newEvent.EventType = EET_GUI_EVENT;
				newEvent.GUIEvent.Caller = this;
				newEvent.GUIEvent.Element = 0;
				newEvent.GUIEvent.EventType = EGET_SCROLL_BAR_CHANGED;
				Parent->OnEvent(newEvent);
			}
			if (absorb)
				return true;
		}
		break;
	case EET_GUI_EVENT:
		if (event.GUIEvent.EventType == EGET_BUTTON_CLICKED)
		{
			if (event.GUIEvent.Caller == UpButton)
				setPos(Pos+SmallStep);
			else
			if (event.GUIEvent.Caller == DownButton)
				setPos(Pos-SmallStep);

			SEvent newEvent;
			newEvent.EventType = EET_GUI_EVENT;
			newEvent.GUIEvent.Caller = this;
			newEvent.GUIEvent.Element = 0;
			newEvent.GUIEvent.EventType = EGET_SCROLL_BAR_CHANGED;
			Parent->OnEvent(newEvent);

			return true;
		}
		else
		if (event.GUIEvent.EventType == EGET_ELEMENT_FOCUS_LOST)
		{
			if (event.GUIEvent.Caller == this)
				Dragging = false;
		}
		break;
	case EET_MOUSE_INPUT_EVENT:
		switch(event.MouseInput.Event)
		{
		case EMIE_MOUSE_WHEEL:
			if (Environment->hasFocus(this) || Environment->hasFocus(UpButton) || Environment->hasFocus(DownButton))
			{
				setPos(getPos() + (s32)event.MouseInput.Wheel* +SmallStep);
				SEvent newEvent;
				newEvent.EventType = EET_GUI_EVENT;
				newEvent.GUIEvent.Caller = this;
				newEvent.GUIEvent.Element = 0;
				newEvent.GUIEvent.EventType = EGET_SCROLL_BAR_CHANGED;
				Parent->OnEvent(newEvent);
				return true;
			}
			break;
		case EMIE_LMOUSE_PRESSED_DOWN:
		{
			if (AbsoluteClippingRect.isPointInside(core::position2di(event.MouseInput.X, event.MouseInput.Y)))
			{
				Dragging = true;
				DraggedBySlider = rect<s32>(AbsoluteRect.UpperLeftCorner + position2d<s32>(SliderX, SliderY),
					AbsoluteRect.UpperLeftCorner + position2d<s32>(SliderX, SliderY) +
					position2d<s32>(Slider[0]->getSize().Width, Slider[0]->getSize().Height)).isPointInside(core::position2di(event.MouseInput.X, event.MouseInput.Y));
				TrayClick = !DraggedBySlider;
				DesiredPos = getPosFromMousePos(event.MouseInput.X, event.MouseInput.Y);
				return true;
			}
			break;
		}
		case EMIE_LMOUSE_LEFT_UP:
		case EMIE_MOUSE_MOVED:
			if (Dragging)
			{
				if (event.MouseInput.Event == EMIE_LMOUSE_LEFT_UP)
					Dragging = false;

				const s32 newPos = getPosFromMousePos(event.MouseInput.X, event.MouseInput.Y);
				const s32 oldPos = Pos;

				if (!DraggedBySlider)
				{
					if (AbsoluteClippingRect.isPointInside(core::position2di(event.MouseInput.X, event.MouseInput.Y)))
					{
						DraggedBySlider = rect<s32>(AbsoluteRect.UpperLeftCorner + position2d<s32>(SliderX, SliderY),
					AbsoluteRect.UpperLeftCorner + position2d<s32>(SliderX, SliderY) +
					position2d<s32>(Slider[0]->getSize().Width, Slider[0]->getSize().Height)).isPointInside(core::position2di(event.MouseInput.X, event.MouseInput.Y));
						TrayClick = !DraggedBySlider;
					}
					else
					{
						TrayClick = false;
						if (event.MouseInput.Event == EMIE_MOUSE_MOVED)
							return true;
					}
				}
				
				if (DraggedBySlider)
				{
					setPos(newPos);
				}
				else
				{
					DesiredPos = newPos;
				}

				if (Pos != oldPos && Parent)
				{
					SEvent newEvent;
					newEvent.EventType = EET_GUI_EVENT;
					newEvent.GUIEvent.Caller = this;
					newEvent.GUIEvent.Element = 0;
					newEvent.GUIEvent.EventType = EGET_SCROLL_BAR_CHANGED;
					Parent->OnEvent(newEvent);
				}
				return true;
			}
			else
			{
				DraggedBySlider = false;
				TrayClick = false;
			}
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}

	return IGUIElement::OnEvent(event);
}

void SSGUIScrollBar::draw()
{
	if (!IsVisible)
		return;

	IGUISkin* skin = Environment->getSkin();
	if (!skin)
		return;

	u32 now = os::Timer::getRealTime();

	if (Dragging && !DraggedBySlider && TrayClick && now > LastChange + 200)
	{
		LastChange = now;

		const s32 oldPos = Pos;

		if (DesiredPos >= Pos + LargeStep)
			setPos(Pos + LargeStep);
		else 
		if (DesiredPos <= Pos - LargeStep)
			setPos(Pos - LargeStep);
		else 
		if (DesiredPos >= Pos - LargeStep && DesiredPos <= Pos + LargeStep)
			setPos(DesiredPos);

		if (Pos != oldPos && Parent)
		{
			SEvent newEvent;
			newEvent.EventType = EET_GUI_EVENT;
			newEvent.GUIEvent.Caller = this;
			newEvent.GUIEvent.Element = 0;
			newEvent.GUIEvent.EventType = EGET_SCROLL_BAR_CHANGED;
			Parent->OnEvent(newEvent);
		}
	}

	// draw buttons
	rect<s32> rect = AbsoluteRect;
	IVideoDriver *driver = Environment->getVideoDriver();
	if (Horizontal)
	{
		driver->draw2DImage(Rule[SSSS_SCROLLBAR_NORMAL], position2d<s32>(rect.UpperLeftCorner.X + DownButton->getRelativePosition().LowerRightCorner.X,
			rect.UpperLeftCorner.Y + s32((rect.getHeight() - Rule[SSSS_SCROLLBAR_NORMAL]->getSize().Height) / 2)),
			core::rect<s32>(0, 0, Rule[SSSS_SCROLLBAR_NORMAL]->getSize().Width, Rule[SSSS_SCROLLBAR_NORMAL]->getSize().Height), 0, SColor(255,255,255,255), true);
		SSGUI_SCROLLBAR_SLIDER_STATES state;
		if (DraggedBySlider || SliderOver && Slider[SSSSLS_SLIDER_MOUSE_OVER]) state = SSSSLS_SLIDER_MOUSE_OVER;
		else state = SSSSLS_SLIDER_NORMAL;
		driver->draw2DImage(Slider[state], position2d<s32>(rect.UpperLeftCorner.X + SliderX, rect.UpperLeftCorner.Y + SliderY),
			core::rect<s32>(0, 0, Slider[state]->getSize().Width, Slider[state]->getSize().Height), 0, SColor(255,255,255,255), true);
	}
	else
	{
		driver->draw2DImage(Rule[0], position2d<s32>(rect.UpperLeftCorner.X + s32((rect.getWidth() - Rule[SSSS_SCROLLBAR_NORMAL]->getSize().Width) / 2),
			rect.UpperLeftCorner.Y + UpButton->getRelativePosition().LowerRightCorner.Y),
			core::rect<s32>(0, 0, Rule[0]->getSize().Width, Rule[0]->getSize().Height), 0, SColor(255,255,255,255), true);
		SSGUI_SCROLLBAR_SLIDER_STATES state;
		if (DraggedBySlider || SliderOver && Slider[SSSSLS_SLIDER_MOUSE_OVER]) state = SSSSLS_SLIDER_MOUSE_OVER;
		else state = SSSSLS_SLIDER_NORMAL;
		driver->draw2DImage(Slider[state], position2d<s32>(rect.UpperLeftCorner.X + SliderX, rect.UpperLeftCorner.Y + SliderY),
			core::rect<s32>(0, 0, Slider[state]->getSize().Width, Slider[state]->getSize().Height), 0, SColor(255,255,255,255), true);
	}
	IGUIElement::draw();
}



void SSGUIScrollBar::setVisualElements(ITexture *ubs_up, ITexture *ubs_over, ITexture *ubs_down, ITexture *ubs_inactive,
									   ITexture *dbs_up, ITexture *dbs_over, ITexture *dbs_down, ITexture *dbs_inactive,
									   ITexture *rs_normal, ITexture *rs_inactive,
									   ITexture *sls_normal, ITexture *sls_over, ITexture *sls_inactive)
{
	if (ubs_up)
	{
			UpButton->setVisualState(SSGBS_BUTTON_UP, ubs_up);
		if (ubs_over)
			UpButton->setVisualState(SSGBS_BUTTON_MOUSE_OVER, ubs_over);
		if (ubs_down)
			UpButton->setVisualState(SSGBS_BUTTON_DOWN, ubs_down);
		if (ubs_inactive)
			UpButton->setVisualState(SSGBS_BUTTON_INACTIVE, ubs_inactive);
	}

	if (dbs_up)
	{
			DownButton->setVisualState(SSGBS_BUTTON_UP, dbs_up);
		if (dbs_over)
			DownButton->setVisualState(SSGBS_BUTTON_MOUSE_OVER, dbs_over);
		if (dbs_down)
			DownButton->setVisualState(SSGBS_BUTTON_DOWN, dbs_down);
		if (dbs_inactive)
			DownButton->setVisualState(SSGBS_BUTTON_INACTIVE, dbs_inactive);
	}

	if (rs_normal)
	{
		if (Rule[SSSS_SCROLLBAR_NORMAL])
			Rule[SSSS_SCROLLBAR_NORMAL]->drop();
		Rule[SSSS_SCROLLBAR_NORMAL] = rs_normal;
		Rule[SSSS_SCROLLBAR_NORMAL]->grab();

		if (rs_inactive)
		{
			if (Rule[SSSS_SCROLLBAR_INACTIVE])
				Rule[SSSS_SCROLLBAR_INACTIVE]->drop();
			Rule[SSSS_SCROLLBAR_INACTIVE] = rs_inactive;
			Rule[SSSS_SCROLLBAR_INACTIVE]->grab();
		}
	}

	if (sls_normal)
	{
		if (Slider[SSSSLS_SLIDER_NORMAL])
			Slider[SSSSLS_SLIDER_NORMAL]->drop();
		Slider[SSSSLS_SLIDER_NORMAL] = sls_normal;
		Slider[SSSSLS_SLIDER_NORMAL]->grab();

		if (sls_over)
		{
			if (Slider[SSSSLS_SLIDER_MOUSE_OVER])
				Slider[SSSSLS_SLIDER_MOUSE_OVER]->drop();
			Slider[SSSSLS_SLIDER_MOUSE_OVER] = sls_over;
			Slider[SSSSLS_SLIDER_MOUSE_OVER]->grab();
		}
		if (sls_inactive)
		{
			if (Slider[SSSSLS_SLIDER_INACTIVE])
				Slider[SSSSLS_SLIDER_INACTIVE]->drop();
			Slider[SSSSLS_SLIDER_INACTIVE] = sls_inactive;
			Slider[SSSSLS_SLIDER_INACTIVE]->grab();
		}
	}

	refreshControls();
}

s32 SSGUIScrollBar::getPosFromMousePos(s32 x, s32 y) const
{
	if (Horizontal)
	{
		return s32(f32(x - SliderRect.UpperLeftCorner.X) / SliderRect.getWidth() * Max);
	}
	else
	{
		return s32((f32)Max - f32(y - SliderRect.UpperLeftCorner.Y) / SliderRect.getHeight() * Max);
	}
}

void SSGUIScrollBar::refreshControls()
{
	rect<s32> rectangle = rect<s32>(0,0,0,0);
	rectangle.UpperLeftCorner = IGUIElement::getRelativePosition().UpperLeftCorner;
	rectangle.LowerRightCorner = IGUIElement::getRelativePosition().UpperLeftCorner;

	if (Horizontal)
	{
		DownButton->setPosition(position2d<s32>(0,0));

		UpButton->setPosition(position2d<s32>(DownButton->getRelativePosition().LowerRightCorner.X +
			Rule[0]->getSize().Width, 0));

		rectangle.LowerRightCorner += UpButton->getRelativePosition().LowerRightCorner;

		IGUIElement::setRelativePosition(rectangle);

		SliderRect = rect<s32>(AbsoluteRect.UpperLeftCorner + position2d<s32>(DownButton->getRelativePosition().getWidth(), 0),
			AbsoluteRect.LowerRightCorner - position2d<s32>(UpButton->getRelativePosition().getWidth(), 0));
	}
	else
	{
		UpButton->setPosition(position2d<s32>(0,0));

		DownButton->setPosition(position2d<s32>(0, UpButton->getRelativePosition().LowerRightCorner.Y +
			Rule[0]->getSize().Height));

		rectangle.LowerRightCorner += DownButton->getRelativePosition().LowerRightCorner;

		IGUIElement::setRelativePosition(rectangle);

		SliderRect = rect<s32>(AbsoluteRect.UpperLeftCorner + position2d<s32>(0, UpButton->getRelativePosition().getHeight()),
			AbsoluteRect.LowerRightCorner - position2d<s32>(0, DownButton->getRelativePosition().getHeight()));
	}

	setPos(Pos);
}

void SSGUIScrollBar::setPosition(const position2d<s32> &pos)
{
	IGUIElement::setRelativePosition(rect<s32>(pos, pos + position2d<s32>(IGUIElement::getRelativePosition().getWidth(), IGUIElement::getRelativePosition().getHeight())));
	refreshControls();
}