#include <irrlicht.h>
#include "SSISceneNodeAnimatorFlyEllipce.h"
#include "SSISceneNodeAnimatorRotation.h"

#ifndef __SS_PLANETS_H_INCLUDED__
#define __SS_PLANETS_H_INCLUDED__

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

//��������� �������� (��� ����������� ���� ������ �������)
extern bool IsActive;
extern f32 koeffSpeed;

//������� ������������� ������
ISceneNode* AddEarth(IVideoDriver* driver, ISceneManager* smgr);
#endif