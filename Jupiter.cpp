#include "SSPlanets.h"

ISceneNode* AddJupiter()
{
	ISceneNode *jupiter = smgr->addSphereSceneNode(45.0f, 32, 0, -1, vector3df(0, 0, 0), vector3df(0, 0, 0), vector3df(1.0, 1.0, 1.0));
	SSRotationAnimator *animJupiterRot = new SSRotationAnimator(vector3df(0, 5.0f / 0.3f, 0), &koeffSpeed, &IsActiveRotating);
	SSFlyEllipceAnimator *animJupiter = new SSFlyEllipceAnimator(sun->getPosition(), 0, 6.0f, 13.0f, &koeffSpeed, kf*650.0f, kf*600.0f, &IsActiveMoving);
	if (jupiter)
	{
		jupiter->setMaterialFlag(EMF_LIGHTING, false);
		jupiter->setMaterialTexture(0, driver->getTexture(".\\data\\jupiter_rgb_cyl_www.jpg"));
		jupiter->addAnimator(animJupiter);
		jupiter->addAnimator(animJupiterRot);
		jupiter->setRotation(vector3df(0.0f, 4.0f, 4.0f));
	}
	return jupiter;
}
