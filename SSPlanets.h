#pragma once
#include <irrlicht.h>
#include "ISceneNodeAnimatorFlyEllipce.h"
#include "ISceneNodeAnimatorRotation.h"

#ifndef __C_SS_PLANETS_H_INCLUDED__
#define __C_SS_PLANETS_H_INCLUDED__

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

//Параметры анимации (для доступности всем файлам проекта)
extern bool IsActive;
extern f32 speed;

//Функции инициализации планет
ISceneNode* AddEarth(IVideoDriver* driver, ISceneManager* smgr);
#endif