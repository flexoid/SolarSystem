#ifndef __SS_GUI_H_INCLUDED__
#define __SS_GUI_H_INCLUDED__

#include "SSGUIElementFactory.h"
#include "SSGUIFunctions.h"

#define GUIDATAWAY "./data/GUI/"

#define SCROLLBAR_ID 10001
#define MENUBAR_ID 10002
#define SIDENAVIGATEBAR_ID 10003
#define SIDEINFOBAR_ID 10004

extern SSGUIElementFactory *Factory;

extern array<IGUIElement*> GUIElements;

extern SSGUIScrollBar *ZoomScrollBar;
extern SSGUIScrollBar *DistanceScrollBar;
extern SSGUIScrollBar *SpeedScrollBar;
extern SSGUIMenuBar *MenuBar;
extern SSGUISideNavigateBar *SideNavigateBar;
extern SSGUISideInfoBar *SideInfoBar;
extern SSGUIStatusBar *StatusBar;
extern SSGUISatelliteInfoWindow *SatelliteInfoWindow;
extern IGUIButton *SatelliteInfoButton;
extern SSGUIAboutWindow *AboutWindow;

extern s32 currentPlanetID;

struct SatelliteInfoParameters
{
	const char *SatelliteInfo;
	rect<s32> SatteliteInfoButtonPosition;
};

struct SideInfoBarStructure
{
	const char *TitleBox;
	const char *ImageBox;
	const char *GInfoBox;
	const char *PHInfoBox;
	//const char *SatelliteInfo;
	SatelliteInfoParameters SatelliteInfo;
};

extern struct SideInfoBarStructure InfoStructures[10];

//						SideNavigateBar
//-----------------------------------------------------------
extern s32 StarGroupID;
extern s32 SunButtonID;

extern s32 PlanetsGroupID;
extern s32 MercuryButtonID;
extern s32 VenusButtonID;
extern s32 EarthButtonID;
extern s32 MarsButtonID;
extern s32 JupiterButtonID;
extern s32 SaturnButtonID;
extern s32 NeptuneButtonID;
extern s32 UranusButtonID;

extern s32 LittlePlanetsGroupID;
extern s32 PlutoButtonID;
//-----------------------------------------------------------

//						SideNavigateBar
//-----------------------------------------------------------
extern SSGUIButton *GlobalViewButton;
extern SSGUIButton *PrevPlanetButton;
extern SSGUIButton *NextPlanetButton;
extern SSGUIButton *FreeFlightButton;
extern SSGUIButton *HelpButton;
extern SSGUIButton *AboutButton;
extern SSGUIButton *MinimizeButton;
extern SSGUIButton *ExitButton;
//-----------------------------------------------------------

extern s32 koeffOfScale;
extern f32 koeffOfDist;


void InitializeGUI(IGUIEnvironment *environment);
void InitializeZoomScrollBar();
void InitializeDistanceScrollBar();
void InitializeSpeedScrollBar();
void InitializeMenuBar();
void InitializeSideNavigateBar();
void InitializeSideInfoBar();
void InitializeSatelliteInfoWindow();
void InitializeAboutWindow();

void FillSideInfoBarStructure();
void FillSideInfoBar(s32 id);

void GlobalView();
void PrevPlanet();
void NextPlanet();
void FreeFlight();
void About();
void Minimize();
void Exit();
void SideNavigateBarCallback(s32 groupID, s32 buttonID);

#endif