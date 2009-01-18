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

//���������� �������� (��� ����������� ���� ������ �������)
extern bool IsActive;

//������� ������������� ������
ISceneNode* AddEarth(IVideoDriver* driver, ISceneManager* smgr);