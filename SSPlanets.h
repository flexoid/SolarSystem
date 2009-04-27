#include <irrlicht.h>
#include "SSFlyEllipceAnimator.h"
#include "SSRotationAnimator.h"

#ifndef __SS_PLANETS_H_INCLUDED__
#define __SS_PLANETS_H_INCLUDED__

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

//��������� �������� (��� ����������� ���� ������ �������)
extern bool IsActiveMoving;
extern bool IsActiveRotating;
extern f32 koeffSpeed;

//���������� ���������� ������
extern IVideoDriver* driver;
extern ISceneManager* smgr;

//���������� �������
extern ISceneNode* sun;

//������� ������������� ������
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

const int kf = 3;

#endif