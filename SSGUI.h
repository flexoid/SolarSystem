#ifndef __SS_GUI_H_INCLUDED__
#define __SS_GUI_H_INCLUDED__

#include "SSGUIElementFactory.h"
#include "SSGUIFunctions.h"

#define DATAWAY ".\\data\\"

#define SCROLLBAR_ID 10001
#define MENUBAR_ID 10002
#define SIDENAVIGATEBAR_ID 10003
#define SIDEINFOBAR_ID 10004

extern SSGUIElementFactory *Factory;

extern SSGUIScrollBar *ZoomScrollBar;
extern SSGUIMenuBar *MenuBar;
extern SSGUISideNavigateBar *SideNavigateBar;
extern SSGUISideInfoBar *SideInfoBar;

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
extern s32 ExitButtonID;
//-----------------------------------------------------------


void InitializeGUI(IGUIEnvironment *environment);

void GlobalView();
void SideNavigateBarCallback(s32 groupID, s32 buttonID);

#endif