#include "SSPlanets.h"

ISceneNode* AddSaturn()
{
	ISceneNode *saturn = smgr->addSphereSceneNode(38.0f, 32, 0, -1, vector3df(0, 0, 0), vector3df(0, 0, 0), vector3df(1.0, 1.0, 1.0));
	SSRotationAnimator *animSaturnRot = new SSRotationAnimator(vector3df(0, 5.0f / 0.4f, 0), &koeffSpeed, &IsActiveRotating);
	SSFlyEllipceAnimator *animSaturn = new SSFlyEllipceAnimator(sun->getPosition(), 0, 5.51f, 9.7f, &koeffSpeed, kf*1000.0f, kf*850.0f, &IsActiveMoving);
	if (saturn)
	{
		saturn->setMaterialFlag(EMF_LIGHTING, false);
		saturn->setMaterialTexture(0, driver->getTexture(".\\data\\saturn.jpg"));
		saturn->addAnimator(animSaturn);
		saturn->addAnimator(animSaturnRot);
		saturn->setRotation(vector3df(0.0f, 26.0f, 26.0f));
	}
	ISceneNode *saturnRings = smgr->addMeshSceneNode(smgr->getMesh(".\\data\\SaturnRings.obj"), saturn);
	saturnRings->setMaterialFlag(EMF_LIGHTING, false);
	saturnRings->setScale(vector3df(2.0f, 2.0f, 2.0f));
	saturnRings->setMaterialTexture(0, driver->getTexture(".\\data\\SaturnRings.png"));
	saturnRings->setMaterialType(EMT_TRANSPARENT_ALPHA_CHANNEL);
	return saturn;
}
