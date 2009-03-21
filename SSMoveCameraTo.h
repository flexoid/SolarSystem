#ifndef __SS_MOVE_CAMERA_TO_H_INCLUDED__
#define __SS_MOVE_CAMERA_TO_H_INCLUDED__

#include <irrlicht.h>
#include <windows.h>

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

using namespace std;

extern IVideoDriver* driver;
extern HANDLE mutex;

void SSMoveCameraTo(ICameraSceneNode* camera, const core::vector3df& endPos, const core::vector3df& target);

#endif