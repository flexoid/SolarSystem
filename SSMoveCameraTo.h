#pragma once;

#include <irrlicht.h>
#include <windows.h>
#include <iostream>

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

using namespace std;

extern IrrlichtDevice* device;
extern ISceneManager* smgr;
extern bool IsActiveMoving;
extern bool IsActiveRotating;

u32 SSMoveCameraTo(ICameraSceneNode* CamToMove, ISceneNode* FinalNode, SSGUISideInfoBar* bar1, SSGUISideNavigateBar* bar2);
void MovingCamera(void);
vector3df CalcFinalPos(ISceneNode* node, f32 length);