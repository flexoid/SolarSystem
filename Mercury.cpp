#include "SSPlanets.h"

ISceneNode* AddMercury()
{
	ISceneNode *mercury = smgr->addSphereSceneNode(1.5f, 32, 0, -1, vector3df(0, 0, 0), vector3df(0, 0, 0), vector3df(1.0, 1.0, 1.0));
	SSRotationAnimator *animMercuryRot = new SSRotationAnimator(vector3df(0, 5.0f / 59.0f, 0), &koeffSpeed, &IsActiveRotating);
	SSFlyEllipceAnimator *animMercury = new SSFlyEllipceAnimator(sun->getPosition(), 0, 3.38f, 47.0f, &koeffSpeed, kf*150.0f, kf*110.0f, &IsActiveMoving);
	if (mercury)
	{
		mercury->setMaterialFlag(EMF_LIGHTING, false);
		mercury->setMaterialTexture(0, driver->getTexture(".\\data\\mercury.jpg"));
		mercury->addAnimator(animMercury);
		mercury->addAnimator(animMercuryRot);
		mercury->setRotation(vector3df(0.0f, 7.0f, 7.0f));
	}
	return mercury;
}
