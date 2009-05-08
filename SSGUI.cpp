#include "SSGUI.h"

s32 mode = -1;

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
s32 FreeFlightButtonID;
s32 HelpButtonID;
s32 AboutButtonID;
s32 MinimizeButtonID;
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

struct SideInfoBarStructure InfoStructures[10];

s32 currentPlanetID = 0;

void InitializeGUI(IGUIEnvironment *environment)
{
	IVideoDriver *driver = environment->getVideoDriver();


	Factory = new SSGUIElementFactory(environment);
	environment->registerGUIElementFactory(Factory);

	//InitializeZoomScrollBar();
	InitializeMenuBar();
	InitializeSideNavigateBar();
	InitializeSideInfoBar();
	FillSideInfoBarStructure();


	/*ZoomScrollBar = (SSGUIScrollBar*)Factory->addGUIElement("scrollbar", 0);
	ZoomScrollBar->setVisualElements(
		driver->getTexture(".\\data\\scroll\\SS\\ub_up.png"),
		driver->getTexture(".\\data\\scroll\\SS\\ub_over.png"),
		driver->getTexture(".\\data\\scroll\\SS\\ub_down.png"),
		0,
		driver->getTexture(".\\data\\scroll\\SS\\db_up.png"),
		driver->getTexture(".\\data\\scroll\\SS\\db_over.png"),
		driver->getTexture(".\\data\\scroll\\SS\\db_down.png"),
		0,
		driver->getTexture(".\\data\\scroll\\SS\\rule.png"),
		0,
		driver->getTexture(".\\data\\scroll\\SS\\sldr_normal.png"),
		driver->getTexture(".\\data\\scroll\\SS\\sldr_over.png"),
		0);
	ZoomScrollBar->setPosition(position2d<s32>(30, 150));

//							MenuBar
//------------------------------------------------------------
	MenuBar = (SSGUIMenuBar*)Factory->addGUIElement("menubar");

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
	SideNavigateBar = (SSGUISideNavigateBar*)Factory->addGUIElement("sidenavigatebar");

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
	SideInfoBar = (SSGUISideInfoBar*)Factory->addGUIElement("sideinfobar", 0);
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
*/
}

void InitializeZoomScrollBar()
{
	IGUIEnvironment *environment = Factory->getGUIEnvironment();
	IVideoDriver *driver = environment->getVideoDriver();
	dimension2d<s32> screenSize = driver->getScreenSize();

	ZoomScrollBar = (SSGUIScrollBar*)Factory->addGUIElement("scrollbar");
}

void InitializeMenuBar()
{
	IGUIEnvironment *environment = Factory->getGUIEnvironment();
	IVideoDriver *driver = environment->getVideoDriver();
	dimension2d<s32> screenSize = driver->getScreenSize();

	ITexture *background = driver->getTexture("./data/GUI/Source/MenuBar/Background/background.png");
	ITexture *separator = driver->getTexture("./data/GUI/Source/MenuBar/Separator/separator.png");

	MenuBar = (SSGUIMenuBar*)Factory->addGUIElement("menubar");

	MenuBar->setBackground(background);
	MenuBar->setSeparator(separator);
	dimension2d<s32> size = MenuBar->getAbsolutePosition().getSize();
	rect<s32> rectangle;
	rectangle.UpperLeftCorner = position2d<s32>(s32((screenSize.Width - size.Width) / 2), s32(size.Height / 10));
	rectangle.LowerRightCorner = rectangle.UpperLeftCorner + size;
	MenuBar->setRelativePosition(rectangle);
	MenuBar->setHCenter(false);
	MenuBar->setVCenter(true);
	MenuBar->setHIndention(15);

	SSGUIButton *GlobalViewButton = (SSGUIButton*)Factory->addGUIElement("button");
	ITexture *gv_b_up = driver->getTexture("./data/GUI/Source/MenuBar/Buttons/GlobalView/b_up.png");
	ITexture *gv_b_mouse_over = driver->getTexture("./data/GUI/Source/MenuBar/Buttons/GlobalView/b_mouse_over.png");
	ITexture *gv_b_down = driver->getTexture("./data/GUI/Source/MenuBar/Buttons/GlobalView/b_down.png");
	GlobalViewButton->setVisualState(SSGBS_BUTTON_UP, gv_b_up);
	GlobalViewButton->setVisualState(SSGBS_BUTTON_MOUSE_OVER, gv_b_mouse_over);
	GlobalViewButton->setVisualState(SSGBS_BUTTON_DOWN, gv_b_down);
	GlobalViewButtonID = MenuBar->addButton((IGUIButton*)GlobalViewButton);
	MenuBar->setIntervalAfterButton(GlobalViewButtonID, 10);
	MenuBar->setSeparatorAfterButton(GlobalViewButtonID, true);
	MenuBar->setCallback(GlobalViewButtonID, GlobalView);

	SSGUIButton *PrevPlanetButton = (SSGUIButton*)Factory->addGUIElement("button");
	ITexture *pp_b_up = driver->getTexture("./data/GUI/Source/MenuBar/Buttons/PrevPlanet/b_up.png");
	ITexture *pp_b_mouse_over = driver->getTexture("./data/GUI/Source/MenuBar/Buttons/PrevPlanet/b_mouse_over.png");
	ITexture *pp_b_down = driver->getTexture("./data/GUI/Source/MenuBar/Buttons/PrevPlanet/b_down.png");
	PrevPlanetButton->setVisualState(SSGBS_BUTTON_UP, pp_b_up);
	PrevPlanetButton->setVisualState(SSGBS_BUTTON_MOUSE_OVER, pp_b_mouse_over);
	PrevPlanetButton->setVisualState(SSGBS_BUTTON_DOWN, pp_b_down);
	PrevPlanetButtonID = MenuBar->addButton((IGUIButton*)PrevPlanetButton);
	MenuBar->setIntervalAfterButton(PrevPlanetButtonID, 3);
	MenuBar->setCallback(PrevPlanetButtonID, PrevPlanet);

	SSGUIButton *NextPlanetButton = (SSGUIButton*)Factory->addGUIElement("button");
	ITexture *np_b_up = driver->getTexture("./data/GUI/Source/MenuBar/Buttons/NextPlanet/b_up.png");
	ITexture *np_b_mouse_over = driver->getTexture("./data/GUI/Source/MenuBar/Buttons/NextPlanet/b_mouse_over.png");
	ITexture *np_b_down = driver->getTexture("./data/GUI/Source/MenuBar/Buttons/NextPlanet/b_down.png");
	NextPlanetButton->setVisualState(SSGBS_BUTTON_UP, np_b_up);
	NextPlanetButton->setVisualState(SSGBS_BUTTON_MOUSE_OVER, np_b_mouse_over);
	NextPlanetButton->setVisualState(SSGBS_BUTTON_DOWN, np_b_down);
	NextPlanetButtonID = MenuBar->addButton((IGUIButton*)NextPlanetButton);
	MenuBar->setIntervalAfterButton(NextPlanetButtonID, 11);
	MenuBar->setSeparatorAfterButton(NextPlanetButtonID, true);
	MenuBar->setCallback(NextPlanetButtonID, NextPlanet);

	SSGUIButton *FreeFlightButton = (SSGUIButton*)Factory->addGUIElement("button");
	ITexture *ff_b_up = driver->getTexture("./data/GUI/Source/MenuBar/Buttons/FreeFlight/b_up.png");
	ITexture *ff_b_mouse_over = driver->getTexture("./data/GUI/Source/MenuBar/Buttons/FreeFlight/b_mouse_over.png");
	ITexture *ff_b_down = driver->getTexture("./data/GUI/Source/MenuBar/Buttons/FreeFlight/b_down.png");
	FreeFlightButton->setVisualState(SSGBS_BUTTON_UP, ff_b_up);
	FreeFlightButton->setVisualState(SSGBS_BUTTON_MOUSE_OVER, ff_b_mouse_over);
	FreeFlightButton->setVisualState(SSGBS_BUTTON_DOWN, ff_b_down);
	FreeFlightButtonID = MenuBar->addButton((IGUIButton*)FreeFlightButton);
	MenuBar->setIntervalAfterButton(FreeFlightButtonID, 11);
	MenuBar->setSeparatorAfterButton(FreeFlightButtonID, true);

	SSGUIButton *HelpButton = (SSGUIButton*)Factory->addGUIElement("button");
	ITexture *h_b_up = driver->getTexture("./data/GUI/Source/MenuBar/Buttons/Help/b_up.png");
	ITexture *h_b_mouse_over = driver->getTexture("./data/GUI/Source/MenuBar/Buttons/Help/b_mouse_over.png");
	ITexture *h_b_down = driver->getTexture("./data/GUI/Source/MenuBar/Buttons/Help/b_down.png");
	HelpButton->setVisualState(SSGBS_BUTTON_UP, h_b_up);
	HelpButton->setVisualState(SSGBS_BUTTON_MOUSE_OVER, h_b_mouse_over);
	HelpButton->setVisualState(SSGBS_BUTTON_DOWN, h_b_down);
	HelpButtonID = MenuBar->addButton((IGUIButton*)HelpButton);
	MenuBar->setIntervalAfterButton(HelpButtonID, 11);
	MenuBar->setSeparatorAfterButton(HelpButtonID, true);

	SSGUIButton *AboutButton = (SSGUIButton*)Factory->addGUIElement("button");
	ITexture *a_b_up = driver->getTexture("./data/GUI/Source/MenuBar/Buttons/About/b_up.png");
	ITexture *a_b_mouse_over = driver->getTexture("./data/GUI/Source/MenuBar/Buttons/About/b_mouse_over.png");
	ITexture *a_b_down = driver->getTexture("./data/GUI/Source/MenuBar/Buttons/About/b_down.png");
	AboutButton->setVisualState(SSGBS_BUTTON_UP, a_b_up);
	AboutButton->setVisualState(SSGBS_BUTTON_MOUSE_OVER, a_b_mouse_over);
	AboutButton->setVisualState(SSGBS_BUTTON_DOWN, a_b_down);
	AboutButtonID = MenuBar->addButton((IGUIButton*)AboutButton);
	MenuBar->setIntervalAfterButton(AboutButtonID, 11);
	MenuBar->setSeparatorAfterButton(AboutButtonID, true);

	SSGUIButton *MinimizeButton = (SSGUIButton*)Factory->addGUIElement("button");
	ITexture *m_b_up = driver->getTexture("./data/GUI/Source/MenuBar/Buttons/Minimize/b_up.png");
	ITexture *m_b_mouse_over = driver->getTexture("./data/GUI/Source/MenuBar/Buttons/Minimize/b_mouse_over.png");
	ITexture *m_b_down = driver->getTexture("./data/GUI/Source/MenuBar/Buttons/Minimize/b_down.png");
	MinimizeButton->setVisualState(SSGBS_BUTTON_UP, m_b_up);
	MinimizeButton->setVisualState(SSGBS_BUTTON_MOUSE_OVER, m_b_mouse_over);
	MinimizeButton->setVisualState(SSGBS_BUTTON_DOWN, m_b_down);
	MinimizeButtonID = MenuBar->addButton((IGUIButton*)MinimizeButton);
	MenuBar->setCallback(MinimizeButtonID, Minimize);

	SSGUIButton *ExitButton = (SSGUIButton*)Factory->addGUIElement("button");
	ITexture *e_b_up = driver->getTexture("./data/GUI/Source/MenuBar/Buttons/Exit/b_up.png");
	ITexture *e_b_mouse_over = driver->getTexture("./data/GUI/Source/MenuBar/Buttons/Exit/b_mouse_over.png");
	ITexture *e_b_down = driver->getTexture("./data/GUI/Source/MenuBar/Buttons/Exit/b_down.png");
	ExitButton->setVisualState(SSGBS_BUTTON_UP, e_b_up);
	ExitButton->setVisualState(SSGBS_BUTTON_MOUSE_OVER, e_b_mouse_over);
	ExitButton->setVisualState(SSGBS_BUTTON_DOWN, e_b_down);
	ExitButtonID = MenuBar->addButton((IGUIButton*)ExitButton);
	MenuBar->setCallback(ExitButtonID, Exit);
}

void InitializeSideNavigateBar()
{
	IGUIEnvironment *environment = Factory->getGUIEnvironment();
	IVideoDriver *driver = environment->getVideoDriver();
	dimension2d<s32> screenSize = driver->getScreenSize();

	ITexture *background = driver->getTexture("./data/GUI/Source/SideNavigateBar/Background/background.png");
	ITexture *b_up = driver->getTexture("./data/GUI/Source/SideNavigateBar/Buttons/b_up.png");
	ITexture *b_mouse_over = driver->getTexture("./data/GUI/Source/SideNavigateBar/Buttons/b_mouse_over.png");
	ITexture *b_down = driver->getTexture("./data/GUI/Source/SideNavigateBar/Buttons/b_down.png");

	IGUIFont *caption_font = environment->getFont("./data/GUI/Fonts/MyraidPro_smbld(18px).xml");
	IGUIFont *groups_caption_font = environment->getFont("./data/GUI/Fonts/TimesNewRoman(10px).xml");
	IGUIFont *groups_button_font = environment->getFont("./data/GUI/Fonts/MyraidPro_bld(14px).xml");

	SideNavigateBar = (SSGUISideNavigateBar*)Factory->addGUIElement("sidenavigatebar");

	SideNavigateBar->setBackground(background);
	SideNavigateBar->setHIndention(2);
	SideNavigateBar->setVIndention(2);

	SideNavigateBar->setCaption(L"Солнечная система", caption_font, SColor(255,255,210,0));
	SideNavigateBar->setCaptionVIndention(7);
	SideNavigateBar->setCaptionCenterAlignment(true);

	SideNavigateBar->setContainerHIndention(50,5);
	SideNavigateBar->setContainerVIndention(20,5);

	SideNavigateBar->setGroupsBoxCaptionFont(groups_caption_font);
	SideNavigateBar->setGroupsBoxCaptionColor(SColor(255,255,210,0));
	SideNavigateBar->setGroupsBoxIntervalBetweenGroups(25);
	SideNavigateBar->setGroupsBoxIntervalAfterGroupCaption(5);
	SideNavigateBar->setGroupsBoxIntervalBetweenGroupButtons(3);
	SideNavigateBar->setLineBetweenGroupsColor(SColor(255,72,71,0));



// groups and buttons
	StarGroupID = SideNavigateBar->createGroup(L"Звезда");

	SSGUIButton *SunButton = (SSGUIButton*)Factory->addGUIElement("button");
	SunButton->setText(L"Солнце");
	SunButtonID = SideNavigateBar->addButtonToGroup(StarGroupID, (IGUIButton*)SunButton);

	

	PlanetsGroupID = SideNavigateBar->createGroup(L"Планеты");

	SSGUIButton *MercuryButton = (SSGUIButton*)Factory->addGUIElement("button");
	MercuryButton->setText(L"Меркурий");
	MercuryButtonID = SideNavigateBar->addButtonToGroup(PlanetsGroupID, (IGUIButton*)MercuryButton);

	SSGUIButton *VenusButton = (SSGUIButton*)Factory->addGUIElement("button");
	VenusButton->setText(L"Венера");
	VenusButtonID = SideNavigateBar->addButtonToGroup(PlanetsGroupID, (IGUIButton*)VenusButton);

	SSGUIButton *EarthButton = (SSGUIButton*)Factory->addGUIElement("button");
	EarthButton->setText(L"Земля");
	EarthButtonID = SideNavigateBar->addButtonToGroup(PlanetsGroupID, (IGUIButton*)EarthButton);

	SSGUIButton *MarsButton = (SSGUIButton*)Factory->addGUIElement("button");
	MarsButton->setText(L"Марс");
	MarsButtonID = SideNavigateBar->addButtonToGroup(PlanetsGroupID, (IGUIButton*)MarsButton);

	SSGUIButton *JupiterButton = (SSGUIButton*)Factory->addGUIElement("button");
	JupiterButton->setText(L"Юпитер");
	JupiterButtonID = SideNavigateBar->addButtonToGroup(PlanetsGroupID, (IGUIButton*)JupiterButton);

	SSGUIButton *SaturnButton = (SSGUIButton*)Factory->addGUIElement("button");
	SaturnButton->setText(L"Сатурн");
	SaturnButtonID = SideNavigateBar->addButtonToGroup(PlanetsGroupID, (IGUIButton*)SaturnButton);

	SSGUIButton *UranusButton = (SSGUIButton*)Factory->addGUIElement("button");
	UranusButton->setText(L"Уран");
	UranusButtonID = SideNavigateBar->addButtonToGroup(PlanetsGroupID, (IGUIButton*)UranusButton);

	SSGUIButton *NeptuneButton = (SSGUIButton*)Factory->addGUIElement("button");
	NeptuneButton->setText(L"Нептун");
	NeptuneButtonID = SideNavigateBar->addButtonToGroup(PlanetsGroupID, (IGUIButton*)NeptuneButton);



	LittlePlanetsGroupID = SideNavigateBar->createGroup(L"Карликовые планеты");

	SSGUIButton *PlutoButton = (SSGUIButton*)Factory->addGUIElement("button");
	PlutoButton->setText(L"Плутон");
	PlutoButtonID = SideNavigateBar->addButtonToGroup(LittlePlanetsGroupID, (IGUIButton*)PlutoButton);
//----------
	SideNavigateBar->setSSButtonElementsForAll(b_up, b_mouse_over, b_down, 0, groups_button_font, SColor(255,0,166,81));

	SideNavigateBar->setAnimationSpeed(4.0f);
	SideNavigateBar->setCallback(SideNavigateBarCallback);

	SideNavigateBar->showX();
}

void InitializeSideInfoBar()
{
	IGUIEnvironment *environment = Factory->getGUIEnvironment();
	IVideoDriver *driver = environment->getVideoDriver();
	dimension2d<s32> screenSize = driver->getScreenSize();

	SideInfoBar = (SSGUISideInfoBar*)Factory->addGUIElement("sideinfobar");

	SideInfoBar->setBackground(driver->getTexture("./data/GUI/Source/SideInfoBar/TitleBox/Background/background.png"),
		driver->getTexture("./data/GUI/Source/SideInfoBar/ImageBox/Background/background.png"),
		driver->getTexture("./data/GUI/Source/SideInfoBar/GInfoBox/Background/background.png"),
		driver->getTexture("./data/GUI/Source/SideInfoBar/PHInfoBox/Background/background.png"));

	SideInfoBar->setHIndention(3);
	SideInfoBar->setVIndention(2);

	SideInfoBar->setAnimationSpeed(2.0f);
	SideInfoBar->hideX();
}

void FillSideInfoBarStructure()
{
	InfoStructures[0].TitleBox = "./data/GUI/Source/SideInfoBar/TitleBox/Data/sun.png";
	InfoStructures[0].ImageBox = "./data/GUI/Source/SideInfoBar/ImageBox/Data/sun.png";
	InfoStructures[0].GInfoBox = "./data/GUI/Source/SideInfoBar/GInfoBox/Data/sun.png";
	InfoStructures[0].PHInfoBox = "./data/GUI/Source/SideInfoBar/PHInfoBox/Data/sun.png";

	InfoStructures[1].TitleBox = "./data/GUI/Source/SideInfoBar/TitleBox/Data/mercury.png";
	InfoStructures[1].ImageBox = "./data/GUI/Source/SideInfoBar/ImageBox/Data/mercury.png";
	InfoStructures[1].GInfoBox = "./data/GUI/Source/SideInfoBar/GInfoBox/Data/mercury.png";
	InfoStructures[1].PHInfoBox = "./data/GUI/Source/SideInfoBar/PHInfoBox/Data/mercury.png";

	InfoStructures[2].TitleBox = "./data/GUI/Source/SideInfoBar/TitleBox/Data/venus.png";
	InfoStructures[2].ImageBox = "./data/GUI/Source/SideInfoBar/ImageBox/Data/venus.png";
	InfoStructures[2].GInfoBox = "./data/GUI/Source/SideInfoBar/GInfoBox/Data/venus.png";
	InfoStructures[2].PHInfoBox = "./data/GUI/Source/SideInfoBar/PHInfoBox/Data/venus.png";

	InfoStructures[3].TitleBox = "./data/GUI/Source/SideInfoBar/TitleBox/Data/earth.png";
	InfoStructures[3].ImageBox = "./data/GUI/Source/SideInfoBar/ImageBox/Data/earth.png";
	InfoStructures[3].GInfoBox = "./data/GUI/Source/SideInfoBar/GInfoBox/Data/earth.png";
	InfoStructures[3].PHInfoBox = "./data/GUI/Source/SideInfoBar/PHInfoBox/Data/earth.png";

	InfoStructures[4].TitleBox = "./data/GUI/Source/SideInfoBar/TitleBox/Data/mars.png";
	InfoStructures[4].ImageBox = "./data/GUI/Source/SideInfoBar/ImageBox/Data/mars.png";
	InfoStructures[4].GInfoBox = "./data/GUI/Source/SideInfoBar/GInfoBox/Data/mars.png";
	InfoStructures[4].PHInfoBox = "./data/GUI/Source/SideInfoBar/PHInfoBox/Data/mars.png";

	InfoStructures[5].TitleBox = "./data/GUI/Source/SideInfoBar/TitleBox/Data/jupiter.png";
	InfoStructures[5].ImageBox = "./data/GUI/Source/SideInfoBar/ImageBox/Data/jupiter.png";
	InfoStructures[5].GInfoBox = "./data/GUI/Source/SideInfoBar/GInfoBox/Data/jupiter.png";
	InfoStructures[5].PHInfoBox = "./data/GUI/Source/SideInfoBar/PHInfoBox/Data/jupiter.png";

	InfoStructures[6].TitleBox = "./data/GUI/Source/SideInfoBar/TitleBox/Data/saturn.png";
	InfoStructures[6].ImageBox = "./data/GUI/Source/SideInfoBar/ImageBox/Data/saturn.png";
	InfoStructures[6].GInfoBox = "./data/GUI/Source/SideInfoBar/GInfoBox/Data/saturn.png";
	InfoStructures[6].PHInfoBox = "./data/GUI/Source/SideInfoBar/PHInfoBox/Data/saturn.png";

	InfoStructures[7].TitleBox = "./data/GUI/Source/SideInfoBar/TitleBox/Data/uranus.png";
	InfoStructures[7].ImageBox = "./data/GUI/Source/SideInfoBar/ImageBox/Data/uranus.png";
	InfoStructures[7].GInfoBox = "./data/GUI/Source/SideInfoBar/GInfoBox/Data/uranus.png";
	InfoStructures[7].PHInfoBox = "./data/GUI/Source/SideInfoBar/PHInfoBox/Data/uranus.png";

	InfoStructures[8].TitleBox = "./data/GUI/Source/SideInfoBar/TitleBox/Data/neptune.png";
	InfoStructures[8].ImageBox = "./data/GUI/Source/SideInfoBar/ImageBox/Data/neptune.png";
	InfoStructures[8].GInfoBox = "./data/GUI/Source/SideInfoBar/GInfoBox/Data/neptune.png";
	InfoStructures[8].PHInfoBox = "./data/GUI/Source/SideInfoBar/PHInfoBox/Data/neptune.png";

	InfoStructures[9].TitleBox = "./data/GUI/Source/SideInfoBar/TitleBox/Data/pluto.png";
	InfoStructures[9].ImageBox = "./data/GUI/Source/SideInfoBar/ImageBox/Data/pluto.png";
	InfoStructures[9].GInfoBox = "./data/GUI/Source/SideInfoBar/GInfoBox/Data/pluto.png";
	InfoStructures[9].PHInfoBox = "./data/GUI/Source/SideInfoBar/PHInfoBox/Data/pluto.png";
}

void FillSideInfoBar(s32 id)
{
	IVideoDriver *driver = Factory->getGUIEnvironment()->getVideoDriver();

	ITexture *TitleBoxX = SideInfoBar->getTitleBox();
	ITexture *ImageBoxX = SideInfoBar->getImageBox();
	ITexture *GInfoBoxX = SideInfoBar->getGInfoBox();
	ITexture *PHInfoBoxX = SideInfoBar->getPHInfoBox();

	ITexture *TitleBox = 0;
	ITexture *ImageBox = 0;
	ITexture *GInfoBox = 0;
	ITexture *PHInfoBox = 0;

	if (id >= 0)
	{
		TitleBox = driver->getTexture(InfoStructures[id].TitleBox);
		ImageBox = driver->getTexture(InfoStructures[id].ImageBox);
		GInfoBox = driver->getTexture(InfoStructures[id].GInfoBox);
		PHInfoBox = driver->getTexture(InfoStructures[id].PHInfoBox);
	}

	SideInfoBar->setTitleBox(TitleBox);
	SideInfoBar->setImageBox(ImageBox);
	SideInfoBar->setGInfoBox(GInfoBox);
	SideInfoBar->setPHInfoBox(PHInfoBox);

	if (TitleBoxX)
		driver->removeTexture(TitleBoxX);

	if (ImageBoxX)
		driver->removeTexture(ImageBoxX);

	if (GInfoBoxX)
		driver->removeTexture(GInfoBoxX);

	if (PHInfoBoxX)
		driver->removeTexture(PHInfoBoxX);
}