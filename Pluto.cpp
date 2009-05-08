#include "SSPlanets.h"

ISceneNode* AddPluto()
{
	ISceneNode *pluto = smgr->addSphereSceneNode(1.0f, 32, 0, -1, vector3df(10, 0, 0), vector3df(0, 0, 0), vector3df(1.0, 1.0, 1.0));
	SSRotationAnimator *animPlutoRot = new SSRotationAnimator(vector3df(0, 5.0f / 6.0f, 0), &koeffSpeed, &IsActiveRotating);
	SSFlyEllipceAnimator *animPluto = new SSFlyEllipceAnimator(sun->getPosition(), 0, 11.3f, 4.6f, &koeffSpeed, 2000.0f, 1700.0f, &koeffOfDist, &IsActiveMoving);
	if (pluto)
	{
		pluto->setMaterialFlag(EMF_LIGHTING, false);
		pluto->setMaterialTexture(0, driver->getTexture("./data/Textures/Hi/Pluto/Pluto.jpg"));
		pluto->addAnimator(animPluto);
		pluto->addAnimator(animPlutoRot);
	}
	return pluto;
}