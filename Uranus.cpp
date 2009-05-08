#include "SSPlanets.h"

ISceneNode* AddUranus()
{
	ISceneNode *uranus = smgr->addSphereSceneNode(15.4f, 32, 0, -1, vector3df(0, 0, 0), vector3df(0, 0, 0), vector3df(1.0, 1.0, 1.0));
	SSRotationAnimator *animUranusRot = new SSRotationAnimator(vector3df(0, 5.0f / 0.45f, 0), &koeffSpeed, &IsActiveRotating);
	SSFlyEllipceAnimator *animUranus = new SSFlyEllipceAnimator(sun->getPosition(), 0, 6.48f, 6.8f, &koeffSpeed, 1400.0f, 1200.0f, &koeffOfDist, &IsActiveMoving);
	if (uranus)
	{
		uranus->setMaterialFlag(EMF_LIGHTING, false);
		uranus->setMaterialTexture(0, driver->getTexture("./data/Textures/Hi/Uranus/Uranus.jpg"));
		uranus->addAnimator(animUranus);
		uranus->addAnimator(animUranusRot);
		uranus->setRotation(vector3df(0.0f, 82.0f, 82.0f));
	}
	return uranus;
}
