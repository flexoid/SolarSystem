#include "SSGUI.h"

SSGUIElementFactory *Factory;

SSGUIScrollBar *ZoomScrollBar;
SSGUIMenuBar *MenuBar;
SSGUISideNavigateBar *SideNavigateBar;
SSGUISideInfoBar *SideInfoBar;

//						SideNavigateBar
//-----------------------------------------------------------
s32 GlobalViewButtonID;
s32 PrevPlanetButtonID;
s32 NextPlanetButtonID;
s32 ExitButtonID;
//-----------------------------------------------------------

//						SideNavigateBar
//-----------------------------------------------------------
s32 StarGroupID;
s32 SunButtonID;

s32 PlanetsGroupID;
s32 MercuryButtonID;
s32 VenusButtonID;
s32 EarthButtonID;
s32 MarsButtonID;
s32 JupiterButtonID;
s32 SaturnButtonID;
s32 NeptuneButtonID;
s32 UranusButtonID;

s32 LittlePlanetsGroupID;
s32 PlutoButtonID;
//-----------------------------------------------------------

void InitializeGUI(IGUIEnvironment *environment)
{
	IVideoDriver *driver = environment->getVideoDriver();


	Factory = new SSGUIElementFactory(environment);
	environment->registerGUIElementFactory(Factory);

//							MenuBar
//------------------------------------------------------------
	MenuBar = (SSGUIMenuBar*)Factory->addGUIElement("MenuBar");

	ITexture *mb_background = driver->getTexture(".\\data\\GUI\\1024x768\\Source\\MenuBar\\background.png");
	ITexture *mb_separator = driver->getTexture(".\\data\\GUI\\1024x768\\Source\\MenuBar\\separator.png");

	MenuBar->setImage(mb_background);
	MenuBar->setSeparator(mb_separator);

	MenuBar->setInterval(3);
	MenuBar->setHIndention(15);
	MenuBar->setVCenter(true);
	//MenuBar->setHCenter(true);
	MenuBar->setRelativePosition(rect<s32>(s32((1024 - 333) / 2), 10, s32((1024 - 333) / 2) + 333, 10 + 39));

	SSGUIButton *GlobalViewButton = (SSGUIButton*)Factory->addGUIElement("button");
	GlobalViewButton->setVisualState(SSGBS_BUTTON_UP, driver->getTexture(".\\data\\GUI\\1024x768\\Source\\MenuBar\\Buttons\\GlobalView\\b_normal.png"));
	GlobalViewButtonID = MenuBar->addButton((IGUIButton*)GlobalViewButton);
	MenuBar->setSeparatorAfterButton(GlobalViewButtonID, true);
	MenuBar->setCallback(GlobalViewButtonID, GlobalView);

	SSGUIButton *PrevPlanetButton = (SSGUIButton*)Factory->addGUIElement("button");
	PrevPlanetButton->setVisualState(SSGBS_BUTTON_UP, driver->getTexture(".\\data\\GUI\\1024x768\\Source\\MenuBar\\Buttons\\PreviousPlanet\\b_normal.png"));
	PrevPlanetButtonID = MenuBar->addButton((IGUIButton*)PrevPlanetButton);

	SSGUIButton *NextPlanetButton = (SSGUIButton*)Factory->addGUIElement("button");
	NextPlanetButton->setVisualState(SSGBS_BUTTON_UP, driver->getTexture(".\\data\\GUI\\1024x768\\Source\\MenuBar\\Buttons\\NextPlanet\\b_normal.png"));
	NextPlanetButtonID = MenuBar->addButton((IGUIButton*)NextPlanetButton);
	MenuBar->setIntervalAfterButton(NextPlanetButtonID, 200);

	SSGUIButton *ExitButton = (SSGUIButton*)Factory->addGUIElement("button");
	ExitButton->setVisualState(SSGBS_BUTTON_UP, driver->getTexture(".\\data\\GUI\\1024x768\\Source\\MenuBar\\Buttons\\Exit\\b_normal.png"));
	ExitButtonID = MenuBar->addButton((IGUIButton*)ExitButton);
	
//------------------------------------------------------------


//						SideNavigateBar
//------------------------------------------------------------
	SideNavigateBar = (SSGUISideNavigateBar*)Factory->addGUIElement("SideNavigateBar");

	ITexture *snb_background = driver->getTexture(".\\data\\GUI\\1024x768\\Source\\SideNavigateBar\\background.png");
	ITexture *snb_b_normal = driver->getTexture(".\\data\\GUI\\1024x768\\Source\\SideNavigateBar\\Buttons\\b_normal.png");
	ITexture *snb_b_over = driver->getTexture(".\\data\\GUI\\1024x768\\Source\\SideNavigateBar\\Buttons\\b_over.png");
	ITexture *snb_b_down = driver->getTexture(".\\data\\GUI\\1024x768\\Source\\SideNavigateBar\\Buttons\\b_down.png");

	SideNavigateBar->setImage(snb_background);

	SideNavigateBar->setHIndention(2);
	SideNavigateBar->setVIndention(2);
	SideNavigateBar->setAnimationSpeed(4.0f);

	SideNavigateBar->setCaptionVIndention(7);
	SideNavigateBar->setCaption(L"Солнечная система", environment->getFont(".\\data\\GUI\\1024x768\\Fonts\\Myraid_pro(18px).xml"), SColor(255, 255, 210, 0));
	SideNavigateBar->setCaptionCenterAlignment(true);

	SideNavigateBar->setContainerHIndention(50, 5);
	SideNavigateBar->setContainerVIndention(20, 5);

	SideNavigateBar->setLineBetweenGroupColor(SColor(255,72,71,0));

	StarGroupID = SideNavigateBar->createGroup(L"");
	SideNavigateBar->setGroupCaption(StarGroupID, L"Звезда", environment->getFont(".\\data\\GUI\\1024x768\\Fonts\\Myraid_pro(8px).xml"), SColor(255,255,255,255), false);
	SideNavigateBar->setIntervalAfterGroupCaption(5);
	SSGUIButton *SunButton = (SSGUIButton*)Factory->addGUIElement("button");
	SunButton->setVisualState(SSGBS_BUTTON_UP, snb_b_normal);
	SunButton->setVisualState(SSGBS_BUTTON_MOUSE_OVER, snb_b_over);
	SunButton->setVisualState(SSGBS_BUTTON_DOWN, snb_b_down);
	SunButton->setOverrideFont(environment->getFont(".\\data\\GUI\\1024x768\\Fonts\\MyraidPro(14px).xml"));
	SunButton->setOverrideColor(SColor(255,0,166,81));
	SunButton->setText(L"Солнце");
	SideNavigateBar->addButtonToGroup(StarGroupID, (IGUIButton*)SunButton);
	SideNavigateBar->setCallback(SideNavigateBarCallback);

	SideNavigateBar->setIntervalBetweenGroups(25);

	PlanetsGroupID = SideNavigateBar->createGroup(L"");
	SideNavigateBar->setGroupCaption(PlanetsGroupID, L"Планеты", environment->getFont(".\\data\\GUI\\1024x768\\Fonts\\Myraid_pro(8px).xml"), SColor(255,255,255,255), false);
	SSGUIButton *MercuryButton = (SSGUIButton*)Factory->addGUIElement("button");
	MercuryButton->setVisualState(SSGBS_BUTTON_UP, snb_b_normal);
	MercuryButton->setVisualState(SSGBS_BUTTON_MOUSE_OVER, snb_b_over);
	MercuryButton->setVisualState(SSGBS_BUTTON_DOWN, snb_b_down);
	MercuryButton->setOverrideFont(environment->getFont(".\\data\\GUI\\1024x768\\Fonts\\MyraidPro(14px).xml"));
	MercuryButton->setOverrideColor(SColor(255,0,166,81));
	MercuryButton->setText(L"Меркурий");
	SideNavigateBar->addButtonToGroup(PlanetsGroupID, (IGUIButton*)MercuryButton);
	SSGUIButton *VenusButton = (SSGUIButton*)Factory->addGUIElement("button");
	VenusButton->setVisualState(SSGBS_BUTTON_UP, snb_b_normal);
	VenusButton->setVisualState(SSGBS_BUTTON_MOUSE_OVER, snb_b_over);
	VenusButton->setVisualState(SSGBS_BUTTON_DOWN, snb_b_down);
	VenusButton->setOverrideFont(environment->getFont(".\\data\\GUI\\1024x768\\Fonts\\MyraidPro(14px).xml"));
	VenusButton->setOverrideColor(SColor(255,0,166,81));
	VenusButton->setText(L"Венера");
	SideNavigateBar->addButtonToGroup(PlanetsGroupID, (IGUIButton*)VenusButton);
	SSGUIButton *EarthButton = (SSGUIButton*)Factory->addGUIElement("button");
	EarthButton->setVisualState(SSGBS_BUTTON_UP, snb_b_normal);
	EarthButton->setVisualState(SSGBS_BUTTON_MOUSE_OVER, snb_b_over);
	EarthButton->setVisualState(SSGBS_BUTTON_DOWN, snb_b_down);
	EarthButton->setOverrideFont(environment->getFont(".\\data\\GUI\\1024x768\\Fonts\\MyraidPro(14px).xml"));
	EarthButton->setOverrideColor(SColor(255,0,166,81));
	EarthButton->setText(L"Земля");
	SideNavigateBar->addButtonToGroup(PlanetsGroupID, (IGUIButton*)EarthButton);
	SSGUIButton *MarsButton = (SSGUIButton*)Factory->addGUIElement("button");
	MarsButton->setVisualState(SSGBS_BUTTON_UP, snb_b_normal);
	MarsButton->setVisualState(SSGBS_BUTTON_MOUSE_OVER, snb_b_over);
	MarsButton->setVisualState(SSGBS_BUTTON_DOWN, snb_b_down);
	MarsButton->setOverrideFont(environment->getFont(".\\data\\GUI\\1024x768\\Fonts\\MyraidPro(14px).xml"));
	MarsButton->setOverrideColor(SColor(255,0,166,81));
	MarsButton->setText(L"Марс");
	SideNavigateBar->addButtonToGroup(PlanetsGroupID, (IGUIButton*)MarsButton);
	SSGUIButton *JupiterButton = (SSGUIButton*)Factory->addGUIElement("button");
	JupiterButton->setVisualState(SSGBS_BUTTON_UP, snb_b_normal);
	JupiterButton->setVisualState(SSGBS_BUTTON_MOUSE_OVER, snb_b_over);
	JupiterButton->setVisualState(SSGBS_BUTTON_DOWN, snb_b_down);
	JupiterButton->setOverrideFont(environment->getFont(".\\data\\GUI\\1024x768\\Fonts\\MyraidPro(14px).xml"));
	JupiterButton->setOverrideColor(SColor(255,0,166,81));
	JupiterButton->setText(L"Юпитер");
	SideNavigateBar->addButtonToGroup(PlanetsGroupID, (IGUIButton*)JupiterButton);
	SSGUIButton *SaturnButton = (SSGUIButton*)Factory->addGUIElement("button");
	SaturnButton->setVisualState(SSGBS_BUTTON_UP, snb_b_normal);
	SaturnButton->setVisualState(SSGBS_BUTTON_MOUSE_OVER, snb_b_over);
	SaturnButton->setVisualState(SSGBS_BUTTON_DOWN, snb_b_down);
	SaturnButton->setOverrideFont(environment->getFont(".\\data\\GUI\\1024x768\\Fonts\\MyraidPro(14px).xml"));
	SaturnButton->setOverrideColor(SColor(255,0,166,81));
	SaturnButton->setText(L"Сатурн");
	SideNavigateBar->addButtonToGroup(PlanetsGroupID, (IGUIButton*)SaturnButton);
	SSGUIButton *UranusButton = (SSGUIButton*)Factory->addGUIElement("button");
	UranusButton->setVisualState(SSGBS_BUTTON_UP, snb_b_normal);
	UranusButton->setVisualState(SSGBS_BUTTON_MOUSE_OVER, snb_b_over);
	UranusButton->setVisualState(SSGBS_BUTTON_DOWN, snb_b_down);
	UranusButton->setOverrideFont(environment->getFont(".\\data\\GUI\\1024x768\\Fonts\\MyraidPro(14px).xml"));
	UranusButton->setOverrideColor(SColor(255,0,166,81));
	UranusButton->setText(L"Уран");
	SideNavigateBar->addButtonToGroup(PlanetsGroupID, (IGUIButton*)UranusButton);
	SSGUIButton *NeptuneButton = (SSGUIButton*)Factory->addGUIElement("button");
	NeptuneButton->setVisualState(SSGBS_BUTTON_UP, snb_b_normal);
	NeptuneButton->setVisualState(SSGBS_BUTTON_MOUSE_OVER, snb_b_over);
	NeptuneButton->setVisualState(SSGBS_BUTTON_DOWN, snb_b_down);
	NeptuneButton->setOverrideFont(environment->getFont(".\\data\\GUI\\1024x768\\Fonts\\MyraidPro(14px).xml"));
	NeptuneButton->setOverrideColor(SColor(255,0,166,81));
	NeptuneButton->setText(L"Нептун");
	SideNavigateBar->addButtonToGroup(PlanetsGroupID, (IGUIButton*)NeptuneButton);

	LittlePlanetsGroupID = SideNavigateBar->createGroup(L"");
	SideNavigateBar->setGroupCaption(LittlePlanetsGroupID, L"Карликовые планеты", environment->getFont(".\\data\\GUI\\1024x768\\Fonts\\Myraid_pro(8px).xml"), SColor(255,255,255,255), false);
	SSGUIButton *PlutoButton = (SSGUIButton*)Factory->addGUIElement("button");
	PlutoButton->setVisualState(SSGBS_BUTTON_UP, snb_b_normal);
	PlutoButton->setVisualState(SSGBS_BUTTON_MOUSE_OVER, snb_b_over);
	PlutoButton->setVisualState(SSGBS_BUTTON_DOWN, snb_b_down);
	PlutoButton->setOverrideFont(environment->getFont(".\\data\\GUI\\1024x768\\Fonts\\MyraidPro(14px).xml"));
	PlutoButton->setOverrideColor(SColor(255,0,166,81));
	PlutoButton->setText(L"Плутон");
	SideNavigateBar->addButtonToGroup(LittlePlanetsGroupID, (IGUIButton*)PlutoButton);
//------------------------------------------------------------

//						SideInfoBar
//------------------------------------------------------------
	SideInfoBar = (SSGUISideInfoBar*)Factory->addGUIElement("SideInfoBar", 0);
	SideInfoBar->setBackground(driver->getTexture(".\\data\\GUI\\SideInfoBar\\TitleBox\\background.png"),
		driver->getTexture(".\\data\\GUI\\SideInfoBar\\ImageBox\\background.png"),
		driver->getTexture(".\\data\\GUI\\SideInfoBar\\PHInfoBox\\background.png"),
		driver->getTexture(".\\data\\GUI\\SideInfoBar\\GInfoBox\\background.png"));


	SideInfoBar->setHIndention(3);
	SideInfoBar->setVIndention(2);
	SideInfoBar->showX();


	SideInfoBar->setTitleBoxCaption(L"Земля", environment->getFont(".\\data\\GUI\\Fonts\\Myraid_pro(18px).xml"), SColor(255, 12, 0, 255));
	SideInfoBar->setImageBoxIcon(driver->getTexture(".\\data\\GUI\\SideInfoBar\\ImageBox\\icon.png"));
	SideInfoBar->setImageBoxImage(driver->getTexture(".\\data\\GUI\\SideInfoBar\\ImageBox\\image.png"));
	SideInfoBar->setImageBoxImageBackground(driver->getTexture(".\\data\\GUI\\SideInfoBar\\ImageBox\\imagebackground.png"));

	SideInfoBar->setGInfoBoxText(L"Земля — третья от Солнца планета Солнечной системы, крупнейшая по диаметру, массе и плотности среди землеподобных планет. Чаще всего упоминается как Земля, Планета Земля, Мир. Единственное известное на данный момент тело Солнечной системы в частности и Вселенной вообще, населённое живыми существами. Научные данные указывают на то, что Земля образовалась около 4,54 млрд лет назад, а вскоре после этого приобрела свой единственный естественный спутник — Луну. Жизнь же, как считается, появилась на Земле 3,5 миллиарда лет назад.",
		environment->getFont(".\\data\\GUI\\1024x768\\Fonts\\ArnoPro_Smbd(9px).xml"), SColor(0,0,255,0));

	SideInfoBar->hideX();
//------------------------------------------------------------
}