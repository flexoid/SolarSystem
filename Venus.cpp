#include "SSPlanets.h"

ISceneNode* AddVenus()
{
	ISceneNode *venus = smgr->addSphereSceneNode(3.7f, 32, 0, -1, vector3df(0, 0, 0), vector3df(0, 0, 0), vector3df(1.0, 1.0, 1.0));
	SSRotationAnimator *animVenusRot = new SSRotationAnimator(vector3df(0, -5.0f / 243.0f, 0), &koeffSpeed, &IsActiveRotating);
	SSFlyEllipceAnimator *animVenus = new SSFlyEllipceAnimator(sun->getPosition(), 0, 3.86f, 35.0f, &koeffSpeed, kf*210.0f, kf*200.0f, &IsActiveMoving);
	if (venus)
	{
		venus->setMaterialFlag(EMF_LIGHTING, false);
		venus->setMaterialTexture(0, driver->getTexture(".\\data\\VenusMap_2500x1250.jpg"));
		venus->addAnimator(animVenus);
		venus->addAnimator(animVenusRot);
		venus->setRotation(vector3df(0.0f, 3.0f, 3.0f));
	}
	return venus;
}
