#pragma once
#include <irrlicht.h>
#include "ISceneNodeAnimatorFlyEllipce.h"
#include "ISceneNodeAnimatorRotation.h"

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

//Активность анимации (для доступности всем файлам проекта)
extern bool IsActive;

//Функции инициализации планет
ISceneNode* AddEarth(IVideoDriver* driver, ISceneManager* smgr);