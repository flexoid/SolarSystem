#pragma once;

#include <irrlicht.h>
#include <windows.h>
#include <iostream>
#include "SSGUI.h"

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

void SSMoveCameraTo(ICameraSceneNode* CamToMove, ISceneNode* FinalNode);
void MovingCamera(void);
vector3df CalcFinalPos(ISceneNode* node, f32 length);
void SSCameraStartPos(ICameraSceneNode* CamToMove);