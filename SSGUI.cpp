#include "SSGUI.h"

SSGUIElementFactory *Factory;

array<IGUIElement*> GUIElements;

SSGUIScrollBar *ZoomScrollBar;
SSGUIScrollBar *DistanceScrollBar;
SSGUIScrollBar *SpeedScrollBar;
SSGUIMenuBar *MenuBar;
SSGUISideNavigateBar *SideNavigateBar;
SSGUISideInfoBar *SideInfoBar;
SSGUISatelliteInfoWindow *SatelliteInfoWindow;
IGUIButton *SatelliteInfoButton;
SSGUIAboutWindow *AboutWindow;

//							MenuBar
//-----------------------------------------------------------
SSGUIButton *GlobalViewButton;
SSGUIButton *PrevPlanetButton;
SSGUIButton *NextPlanetButton;
SSGUIButton *FreeFlightButton;
SSGUIButton *HelpButton;
SSGUIButton *AboutButton;
SSGUIButton *MinimizeButton;
SSGUIButton *ExitButton;
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

	InitializeZoomScrollBar();
	InitializeDistanceScrollBar();
	InitializeSpeedScrollBar();
	InitializeMenuBar();
	InitializeSideNavigateBar();
	InitializeSideInfoBar();	
	InitializeSatelliteInfoWindow();
	InitializeAboutWindow();
	FillSideInfoBarStructure();
}

void InitializeZoomScrollBar()
{
	IGUIEnvironment *environment = Factory->getGUIEnvironment();
	IVideoDriver *driver = environment->getVideoDriver();
	dimension2d<s32> screenSize = driver->getScreenSize();

	ZoomScrollBar = (SSGUIScrollBar*)Factory->addGUIElement("scrollbar");
	ZoomScrollBar->setVisualElements(
		driver->getTexture("./data/GUI/Source/ZoomScrollBar/Buttons/UpButton/b_normal.png"),
		driver->getTexture("./data/GUI/Source/ZoomScrollBar/Buttons/UpButton/b_mouse_over.png"),
		driver->getTexture("./data/GUI/Source/ZoomScrollBar/Buttons/UpButton/b_down.png"),
		0,
		driver->getTexture("./data/GUI/Source/ZoomScrollBar/Buttons/DownButton/b_normal.png"),
		driver->getTexture("./data/GUI/Source/ZoomScrollBar/Buttons/DownButton/b_mouse_over.png"),
		driver->getTexture("./data/GUI/Source/ZoomScrollBar/Buttons/DownButton/b_down.png"),
		0,
		driver->getTexture("./data/GUI/Source/ZoomScrollBar/Rule/rule_normal.png"),
		0,
		driver->getTexture("./data/GUI/Source/ZoomScrollBar/Slider/sldr_normal.png"),
		driver->getTexture("./data/GUI/Source/ZoomScrollBar/Slider/sldr_mouse_over.png"),
		0);
	ZoomScrollBar->setPosition(position2d<s32>(20, 150));
	ZoomScrollBar->setMax(7500);
	ZoomScrollBar->setPos(3750);
	ZoomScrollBar->setSmallStep(500);
	ZoomScrollBar->setLargeStep(1000);

	koeffOfScale = ZoomScrollBar->getPos();
	ZoomScrollBar->setVisible(false);

	ZoomScrollBar->setHelpText(L"Испльзуйте для приближения/удаления камеры");

	GUIElements.push_back(ZoomScrollBar);
}

void InitializeDistanceScrollBar()
{
	IGUIEnvironment *environment = Factory->getGUIEnvironment();
	IVideoDriver *driver = environment->getVideoDriver();
	dimension2d<s32> screenSize = driver->getScreenSize();

	DistanceScrollBar = (SSGUIScrollBar*)Factory->addGUIElement("scrollbar");
	DistanceScrollBar->setVisualElements(
		driver->getTexture("./data/GUI/Source/DistanceScrollBar/Buttons/UpButton/b_normal.png"),
		driver->getTexture("./data/GUI/Source/DistanceScrollBar/Buttons/UpButton/b_mouse_over.png"),
		driver->getTexture("./data/GUI/Source/DistanceScrollBar/Buttons/UpButton/b_down.png"),
		0,
		driver->getTexture("./data/GUI/Source/DistanceScrollBar/Buttons/DownButton/b_normal.png"),
		driver->getTexture("./data/GUI/Source/DistanceScrollBar/Buttons/DownButton/b_mouse_over.png"),
		driver->getTexture("./data/GUI/Source/DistanceScrollBar/Buttons/DownButton/b_down.png"),
		0,
		driver->getTexture("./data/GUI/Source/DistanceScrollBar/Rule/rule_normal.png"),
		0,
		driver->getTexture("./data/GUI/Source/DistanceScrollBar/Slider/sldr_normal.png"),
		driver->getTexture("./data/GUI/Source/DistanceScrollBar/Slider/sldr_mouse_over.png"),
		0);
	DistanceScrollBar->setOrientation(true);
	DistanceScrollBar->setPosition(position2d<s32>(driver->getScreenSize().Width / 2 - DistanceScrollBar->getAbsolutePosition().getWidth() / 2, driver->getScreenSize().Height - 50 - DistanceScrollBar->getAbsolutePosition().getHeight()));
	DistanceScrollBar->setMax(8000);
	DistanceScrollBar->setPos((s32)(koeffOfDist * 1000.0f));
	DistanceScrollBar->setSmallStep(500);
	DistanceScrollBar->setLargeStep(1000);

	DistanceScrollBar->setHelpText(L"Используйте для изменения расстояния между планетами");

	GUIElements.push_back(DistanceScrollBar);
}

void InitializeSpeedScrollBar()
{
	IGUIEnvironment *environment = Factory->getGUIEnvironment();
	IVideoDriver *driver = environment->getVideoDriver();
	dimension2d<s32> screenSize = driver->getScreenSize();

	SpeedScrollBar = (SSGUIScrollBar*)Factory->addGUIElement("scrollbar");
	SpeedScrollBar->setVisualElements(
		driver->getTexture("./data/GUI/Source/SpeedScrollBar/Buttons/UpButton/b_normal.png"),
		driver->getTexture("./data/GUI/Source/SpeedScrollBar/Buttons/UpButton/b_mouse_over.png"),
		driver->getTexture("./data/GUI/Source/SpeedScrollBar/Buttons/UpButton/b_down.png"),
		0,
		driver->getTexture("./data/GUI/Source/SpeedScrollBar/Buttons/DownButton/b_normal.png"),
		driver->getTexture("./data/GUI/Source/SpeedScrollBar/Buttons/DownButton/b_mouse_over.png"),
		driver->getTexture("./data/GUI/Source/SpeedScrollBar/Buttons/DownButton/b_down.png"),
		0,
		driver->getTexture("./data/GUI/Source/SpeedScrollBar/Rule/rule_normal.png"),
		0,
		driver->getTexture("./data/GUI/Source/SpeedScrollBar/Slider/sldr_normal.png"),
		driver->getTexture("./data/GUI/Source/SpeedScrollBar/Slider/sldr_mouse_over.png"),
		0);
	SpeedScrollBar->setPosition(position2d<s32>(20,30));
	SpeedScrollBar->setMax(50000);

	SpeedScrollBar->setHelpText(L"Используйте для настройки скорости движения планет");

	GUIElements.push_back(SpeedScrollBar);
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

	GlobalViewButton = (SSGUIButton*)Factory->addGUIElement("button");
	ITexture *gv_b_up = driver->getTexture("./data/GUI/Source/MenuBar/Buttons/GlobalView/b_up.png");
	ITexture *gv_b_mouse_over = driver->getTexture("./data/GUI/Source/MenuBar/Buttons/GlobalView/b_mouse_over.png");
	ITexture *gv_b_down = driver->getTexture("./data/GUI/Source/MenuBar/Buttons/GlobalView/b_down.png");
	GlobalViewButton->setVisualState(SSGBS_BUTTON_UP, gv_b_up);
	GlobalViewButton->setVisualState(SSGBS_BUTTON_MOUSE_OVER, gv_b_mouse_over);
	GlobalViewButton->setVisualState(SSGBS_BUTTON_DOWN, gv_b_down);
	GlobalViewButton->setHelpText(L"Главный вид");
	s32 GlobalViewButtonID = MenuBar->addButton((IGUIButton*)GlobalViewButton);
	MenuBar->setIntervalAfterButton(GlobalViewButtonID, 10);
	MenuBar->setSeparatorAfterButton(GlobalViewButtonID, true);
	MenuBar->setCallback(GlobalViewButtonID, GlobalView);

	PrevPlanetButton = (SSGUIButton*)Factory->addGUIElement("button");
	ITexture *pp_b_up = driver->getTexture("./data/GUI/Source/MenuBar/Buttons/PrevPlanet/b_up.png");
	ITexture *pp_b_mouse_over = driver->getTexture("./data/GUI/Source/MenuBar/Buttons/PrevPlanet/b_mouse_over.png");
	ITexture *pp_b_down = driver->getTexture("./data/GUI/Source/MenuBar/Buttons/PrevPlanet/b_down.png");
	PrevPlanetButton->setVisualState(SSGBS_BUTTON_UP, pp_b_up);
	PrevPlanetButton->setVisualState(SSGBS_BUTTON_MOUSE_OVER, pp_b_mouse_over);
	PrevPlanetButton->setVisualState(SSGBS_BUTTON_DOWN, pp_b_down);
	PrevPlanetButton->setHelpText(L"Переход к предыдущей планете");
	s32 PrevPlanetButtonID = MenuBar->addButton((IGUIButton*)PrevPlanetButton);
	MenuBar->setIntervalAfterButton(PrevPlanetButtonID, 3);
	MenuBar->setCallback(PrevPlanetButtonID, PrevPlanet);

	NextPlanetButton = (SSGUIButton*)Factory->addGUIElement("button");
	ITexture *np_b_up = driver->getTexture("./data/GUI/Source/MenuBar/Buttons/NextPlanet/b_up.png");
	ITexture *np_b_mouse_over = driver->getTexture("./data/GUI/Source/MenuBar/Buttons/NextPlanet/b_mouse_over.png");
	ITexture *np_b_down = driver->getTexture("./data/GUI/Source/MenuBar/Buttons/NextPlanet/b_down.png");
	NextPlanetButton->setVisualState(SSGBS_BUTTON_UP, np_b_up);
	NextPlanetButton->setVisualState(SSGBS_BUTTON_MOUSE_OVER, np_b_mouse_over);
	NextPlanetButton->setVisualState(SSGBS_BUTTON_DOWN, np_b_down);
	NextPlanetButton->setHelpText(L"Переход к следующей планете");
	s32 NextPlanetButtonID = MenuBar->addButton((IGUIButton*)NextPlanetButton);
	MenuBar->setIntervalAfterButton(NextPlanetButtonID, 11);
	MenuBar->setSeparatorAfterButton(NextPlanetButtonID, true);
	MenuBar->setCallback(NextPlanetButtonID, NextPlanet);

	FreeFlightButton = (SSGUIButton*)Factory->addGUIElement("button");
	ITexture *ff_b_up = driver->getTexture("./data/GUI/Source/MenuBar/Buttons/FreeFlight/b_up.png");
	ITexture *ff_b_mouse_over = driver->getTexture("./data/GUI/Source/MenuBar/Buttons/FreeFlight/b_mouse_over.png");
	ITexture *ff_b_down = driver->getTexture("./data/GUI/Source/MenuBar/Buttons/FreeFlight/b_down.png");
	FreeFlightButton->setVisualState(SSGBS_BUTTON_UP, ff_b_up);
	FreeFlightButton->setVisualState(SSGBS_BUTTON_MOUSE_OVER, ff_b_mouse_over);
	FreeFlightButton->setVisualState(SSGBS_BUTTON_DOWN, ff_b_down);
	FreeFlightButton->setHelpText(L"Режим свободного полета");
	s32 FreeFlightButtonID = MenuBar->addButton((IGUIButton*)FreeFlightButton);
	MenuBar->setIntervalAfterButton(FreeFlightButtonID, 11);
	MenuBar->setSeparatorAfterButton(FreeFlightButtonID, true);
	MenuBar->setCallback(FreeFlightButtonID, FreeFlight);

	/*HelpButton = (SSGUIButton*)Factory->addGUIElement("button");
	ITexture *h_b_up = driver->getTexture("./data/GUI/Source/MenuBar/Buttons/Help/b_up.png");
	ITexture *h_b_mouse_over = driver->getTexture("./data/GUI/Source/MenuBar/Buttons/Help/b_mouse_over.png");
	ITexture *h_b_down = driver->getTexture("./data/GUI/Source/MenuBar/Buttons/Help/b_down.png");
	HelpButton->setVisualState(SSGBS_BUTTON_UP, h_b_up);
	HelpButton->setVisualState(SSGBS_BUTTON_MOUSE_OVER, h_b_mouse_over);
	HelpButton->setVisualState(SSGBS_BUTTON_DOWN, h_b_down);
	HelpButton->setHelpText(L"Справочник");
	s32 HelpButtonID = MenuBar->addButton((IGUIButton*)HelpButton);
	MenuBar->setIntervalAfterButton(HelpButtonID, 11);
	MenuBar->setSeparatorAfterButton(HelpButtonID, true);*/

	AboutButton = (SSGUIButton*)Factory->addGUIElement("button");
	ITexture *a_b_up = driver->getTexture("./data/GUI/Source/MenuBar/Buttons/About/b_up.png");
	ITexture *a_b_mouse_over = driver->getTexture("./data/GUI/Source/MenuBar/Buttons/About/b_mouse_over.png");
	ITexture *a_b_down = driver->getTexture("./data/GUI/Source/MenuBar/Buttons/About/b_down.png");
	AboutButton->setVisualState(SSGBS_BUTTON_UP, a_b_up);
	AboutButton->setVisualState(SSGBS_BUTTON_MOUSE_OVER, a_b_mouse_over);
	AboutButton->setVisualState(SSGBS_BUTTON_DOWN, a_b_down);
	AboutButton->setHelpText(L"О программе");
	s32 AboutButtonID = MenuBar->addButton((IGUIButton*)AboutButton);
	MenuBar->setIntervalAfterButton(AboutButtonID, 11);
	MenuBar->setSeparatorAfterButton(AboutButtonID, true);
	MenuBar->setCallback(AboutButtonID, About);

	/*MinimizeButton = (SSGUIButton*)Factory->addGUIElement("button");
	ITexture *m_b_up = driver->getTexture("./data/GUI/Source/MenuBar/Buttons/Minimize/b_up.png");
	ITexture *m_b_mouse_over = driver->getTexture("./data/GUI/Source/MenuBar/Buttons/Minimize/b_mouse_over.png");
	ITexture *m_b_down = driver->getTexture("./data/GUI/Source/MenuBar/Buttons/Minimize/b_down.png");
	MinimizeButton->setVisualState(SSGBS_BUTTON_UP, m_b_up);
	MinimizeButton->setVisualState(SSGBS_BUTTON_MOUSE_OVER, m_b_mouse_over);
	MinimizeButton->setVisualState(SSGBS_BUTTON_DOWN, m_b_down);
	MinimizeButton->setHelpText(L"Свернуть программу");
	s32 MinimizeButtonID = MenuBar->addButton((IGUIButton*)MinimizeButton);
	MenuBar->setCallback(MinimizeButtonID, Minimize);*/

	ExitButton = (SSGUIButton*)Factory->addGUIElement("button");
	ITexture *e_b_up = driver->getTexture("./data/GUI/Source/MenuBar/Buttons/Exit/b_up.png");
	ITexture *e_b_mouse_over = driver->getTexture("./data/GUI/Source/MenuBar/Buttons/Exit/b_mouse_over.png");
	ITexture *e_b_down = driver->getTexture("./data/GUI/Source/MenuBar/Buttons/Exit/b_down.png");
	ExitButton->setVisualState(SSGBS_BUTTON_UP, e_b_up);
	ExitButton->setVisualState(SSGBS_BUTTON_MOUSE_OVER, e_b_mouse_over);
	ExitButton->setVisualState(SSGBS_BUTTON_DOWN, e_b_down);
	ExitButton->setHelpText(L"Выйти из программы");
	s32 ExitButtonID = MenuBar->addButton((IGUIButton*)ExitButton);
	MenuBar->setCallback(ExitButtonID, Exit);

	GUIElements.push_back(MenuBar);
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

	GUIElements.push_back(SideNavigateBar);
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

	SatelliteInfoButton = environment->addButton(rect<s32>(0,0,0,0), SideInfoBar);
	SatelliteInfoButton->setDrawBorder(false);

	GUIElements.push_back(SideInfoBar);
}

void InitializeSatelliteInfoWindow()
{
	SatelliteInfoWindow = new SSGUISatelliteInfoWindow(Factory->getGUIEnvironment());
	SatelliteInfoWindow->setShowTime(100);
	SatelliteInfoWindow->setHelpText(L"Для закрытия таблицы кликните по ней");
}

void InitializeAboutWindow()
{
	AboutWindow = new SSGUIAboutWindow(Factory->getGUIEnvironment());
	AboutWindow->setShowTime(500);
}

void FillSideInfoBarStructure()
{
	InfoStructures[0].TitleBox = "./data/GUI/Source/SideInfoBar/TitleBox/Data/sun.png";
	InfoStructures[0].ImageBox = "./data/GUI/Source/SideInfoBar/ImageBox/Data/sun.png";
	InfoStructures[0].GInfoBox = "./data/GUI/Source/SideInfoBar/GInfoBox/Data/sun.png";
	InfoStructures[0].PHInfoBox = "./data/GUI/Source/SideInfoBar/PHInfoBox/Data/sun.png";
	InfoStructures[0].SatelliteInfo.SatelliteInfo = 0;
	InfoStructures[0].SatelliteInfo.SatteliteInfoButtonPosition = rect<s32>(0,0,0,0);

	InfoStructures[1].TitleBox = "./data/GUI/Source/SideInfoBar/TitleBox/Data/mercury.png";
	InfoStructures[1].ImageBox = "./data/GUI/Source/SideInfoBar/ImageBox/Data/mercury.png";
	InfoStructures[1].GInfoBox = "./data/GUI/Source/SideInfoBar/GInfoBox/Data/mercury.png";
	InfoStructures[1].PHInfoBox = "./data/GUI/Source/SideInfoBar/PHInfoBox/Data/mercury.png";
	InfoStructures[1].SatelliteInfo.SatelliteInfo = 0;
	InfoStructures[1].SatelliteInfo.SatteliteInfoButtonPosition = rect<s32>(0,0,0,0);

	InfoStructures[2].TitleBox = "./data/GUI/Source/SideInfoBar/TitleBox/Data/venus.png";
	InfoStructures[2].ImageBox = "./data/GUI/Source/SideInfoBar/ImageBox/Data/venus.png";
	InfoStructures[2].GInfoBox = "./data/GUI/Source/SideInfoBar/GInfoBox/Data/venus.png";
	InfoStructures[2].PHInfoBox = "./data/GUI/Source/SideInfoBar/PHInfoBox/Data/venus.png";
	InfoStructures[2].SatelliteInfo.SatelliteInfo = 0;
	InfoStructures[2].SatelliteInfo.SatteliteInfoButtonPosition = rect<s32>(0,0,0,0);

	InfoStructures[3].TitleBox = "./data/GUI/Source/SideInfoBar/TitleBox/Data/earth.png";
	InfoStructures[3].ImageBox = "./data/GUI/Source/SideInfoBar/ImageBox/Data/earth.png";
	InfoStructures[3].GInfoBox = "./data/GUI/Source/SideInfoBar/GInfoBox/Data/earth.png";
	InfoStructures[3].PHInfoBox = "./data/GUI/Source/SideInfoBar/PHInfoBox/Data/earth.png";
	InfoStructures[3].SatelliteInfo.SatelliteInfo = "./data/GUI/Source/SideInfoBar/SatelliteInfo/earth.png";
	InfoStructures[3].SatelliteInfo.SatteliteInfoButtonPosition = rect<s32>(171,516,171+61,516+14);

	InfoStructures[4].TitleBox = "./data/GUI/Source/SideInfoBar/TitleBox/Data/mars.png";
	InfoStructures[4].ImageBox = "./data/GUI/Source/SideInfoBar/ImageBox/Data/mars.png";
	InfoStructures[4].GInfoBox = "./data/GUI/Source/SideInfoBar/GInfoBox/Data/mars.png";
	InfoStructures[4].PHInfoBox = "./data/GUI/Source/SideInfoBar/PHInfoBox/Data/mars.png";
	InfoStructures[4].SatelliteInfo.SatelliteInfo = "./data/GUI/Source/SideInfoBar/SatelliteInfo/mars.png";
	InfoStructures[4].SatelliteInfo.SatteliteInfoButtonPosition = rect<s32>(171,513,171+61,513+14);

	InfoStructures[5].TitleBox = "./data/GUI/Source/SideInfoBar/TitleBox/Data/jupiter.png";
	InfoStructures[5].ImageBox = "./data/GUI/Source/SideInfoBar/ImageBox/Data/jupiter.png";
	InfoStructures[5].GInfoBox = "./data/GUI/Source/SideInfoBar/GInfoBox/Data/jupiter.png";
	InfoStructures[5].PHInfoBox = "./data/GUI/Source/SideInfoBar/PHInfoBox/Data/jupiter.png";
	InfoStructures[5].SatelliteInfo.SatelliteInfo = "./data/GUI/Source/SideInfoBar/SatelliteInfo/jupiter.png";
	InfoStructures[5].SatelliteInfo.SatteliteInfoButtonPosition = rect<s32>(176,513,178+61,513+14);

	InfoStructures[6].TitleBox = "./data/GUI/Source/SideInfoBar/TitleBox/Data/saturn.png";
	InfoStructures[6].ImageBox = "./data/GUI/Source/SideInfoBar/ImageBox/Data/saturn.png";
	InfoStructures[6].GInfoBox = "./data/GUI/Source/SideInfoBar/GInfoBox/Data/saturn.png";
	InfoStructures[6].PHInfoBox = "./data/GUI/Source/SideInfoBar/PHInfoBox/Data/saturn.png";
	InfoStructures[6].SatelliteInfo.SatelliteInfo = "./data/GUI/Source/SideInfoBar/SatelliteInfo/saturn.png";
	InfoStructures[6].SatelliteInfo.SatteliteInfoButtonPosition = rect<s32>(173,513,173+61,513+14);

	InfoStructures[7].TitleBox = "./data/GUI/Source/SideInfoBar/TitleBox/Data/uranus.png";
	InfoStructures[7].ImageBox = "./data/GUI/Source/SideInfoBar/ImageBox/Data/uranus.png";
	InfoStructures[7].GInfoBox = "./data/GUI/Source/SideInfoBar/GInfoBox/Data/uranus.png";
	InfoStructures[7].PHInfoBox = "./data/GUI/Source/SideInfoBar/PHInfoBox/Data/uranus.png";
	InfoStructures[7].SatelliteInfo.SatelliteInfo = "./data/GUI/Source/SideInfoBar/SatelliteInfo/uranus.png";
	InfoStructures[7].SatelliteInfo.SatteliteInfoButtonPosition = rect<s32>(173,513,173+61,513+14);

	InfoStructures[8].TitleBox = "./data/GUI/Source/SideInfoBar/TitleBox/Data/neptune.png";
	InfoStructures[8].ImageBox = "./data/GUI/Source/SideInfoBar/ImageBox/Data/neptune.png";
	InfoStructures[8].GInfoBox = "./data/GUI/Source/SideInfoBar/GInfoBox/Data/neptune.png";
	InfoStructures[8].PHInfoBox = "./data/GUI/Source/SideInfoBar/PHInfoBox/Data/neptune.png";
	InfoStructures[8].SatelliteInfo.SatelliteInfo = "./data/GUI/Source/SideInfoBar/SatelliteInfo/neptune.png";
	InfoStructures[8].SatelliteInfo.SatteliteInfoButtonPosition = rect<s32>(173,521,173+61,521+14);

	InfoStructures[9].TitleBox = "./data/GUI/Source/SideInfoBar/TitleBox/Data/pluto.png";
	InfoStructures[9].ImageBox = "./data/GUI/Source/SideInfoBar/ImageBox/Data/pluto.png";
	InfoStructures[9].GInfoBox = "./data/GUI/Source/SideInfoBar/GInfoBox/Data/pluto.png";
	InfoStructures[9].PHInfoBox = "./data/GUI/Source/SideInfoBar/PHInfoBox/Data/pluto.png";
	InfoStructures[9].SatelliteInfo.SatelliteInfo = "./data/GUI/Source/SideInfoBar/SatelliteInfo/pluto.png";
	InfoStructures[9].SatelliteInfo.SatteliteInfoButtonPosition = rect<s32>(168,521,168+61,521+14);
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
		SatelliteInfoButton->setRelativePosition(InfoStructures[id].SatelliteInfo.SatteliteInfoButtonPosition);
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