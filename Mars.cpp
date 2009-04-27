#include "SSPlanets.h"

ISceneNode* AddMars()
{
	ISceneNode *mars = smgr->addSphereSceneNode(2.0f, 32, 0, -1, vector3df(0, 0, 0), vector3df(0, 0, 0), vector3df(1.0, 1.0, 1.0));
	SSRotationAnimator *animMarsRot = new SSRotationAnimator(vector3df(0, 5.0f / 1.0f, 0), &koeffSpeed, &IsActiveRotating);
	SSFlyEllipceAnimator *animMars = new SSFlyEllipceAnimator(sun->getPosition(), 0, 5.65f, 24.1f, &koeffSpeed, kf*491.0f, kf*420.0f, &IsActiveMoving);
	if (mars)
	{
		mars->setMaterialFlag(EMF_LIGHTING, false);
		mars->setMaterialTexture(0, driver->getTexture(".\\data\\MarsMap_2.jpg"));
		mars->addAnimator(animMars);
		mars->addAnimator(animMarsRot);
		mars->setRotation(vector3df(0.0f, 25.0f, 25.0f));
	}
	return mars;
}
