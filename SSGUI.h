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

extern SSGUIScrollBar *ZoomScrollBar;
extern SSGUIMenuBar *MenuBar;
extern SSGUISideNavigateBar *SideNavigateBar;
extern SSGUISideInfoBar *SideInfoBar;

extern s32 currentPlanetID;

struct SideInfoBarStructure
{
	const char *TitleBox;
	const char *ImageBox;
	const char *GInfoBox;
	const char *PHInfoBox;
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
extern s32 GlobalViewButtonID;
extern s32 PrevPlanetButtonID;
extern s32 NextPlanetButtonID;
extern s32 FreeFlightButtonID;
extern s32 HelpButtonID;
extern s32 AboutButtonID;
extern s32 MinimizeButtonID;
extern s32 ExitButtonID;
//-----------------------------------------------------------


void InitializeGUI(IGUIEnvironment *environment);
void InitializeZoomScrollBar();
void InitializeMenuBar();
void InitializeSideNavigateBar();
void InitializeSideInfoBar();

void FillSideInfoBarStructure();
void FillSideInfoBar(s32 id);

void GlobalView();
void PrevPlanet();
void NextPlanet();
void FreeFlight();
void Minimize();
void Exit();
void SideNavigateBarCallback(s32 groupID, s32 buttonID);

#endif