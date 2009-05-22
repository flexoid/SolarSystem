#pragma once;

#include <irrlicht.h>
#include "SSFlyEllipceAnimator.h"
#include "SSRotationAnimator.h"
#include <string>

#ifndef __SS_PLANETS_H_INCLUDED__
#define __SS_PLANETS_H_INCLUDED__

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

extern array<ISceneNode*> Planets;

//ѕараметры анимации (дл€ доступности всем файлам проекта)
extern bool IsActiveMoving;
extern bool IsActiveRotating;
extern f32 koeffSpeed;
extern f32 koeffOfDist;

//√лобальные экземпл€ры класса
extern IVideoDriver* driver;
extern ISceneManager* smgr;

//√лобальные обьекты
extern ISceneNode* sun;

extern std::string PathToTextures;

//‘ункции инициализации планет
ISceneNode* AddSun();
ISceneNode* AddEarth();
ISceneNode* AddPluto();
ISceneNode* AddMercury();
ISceneNode* AddVenus();
ISceneNode* AddMars();
ISceneNode* AddJupiter();
ISceneNode* AddSaturn();
ISceneNode* AddUranus();
ISceneNode* AddNeptune();

#endif