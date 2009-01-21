#include "SSPlanets.h"

ISceneNode* AddEarth()
{
	//---------Демонстрация
	ISceneNode *earth = smgr->addSphereSceneNode(1.0, 16, 0, -1, vector3df(10, 0, 0), vector3df(0, 0, 0), vector3df(1.0, 1.0, 1.0));
	SSISceneNodeAnimatorRotation *animEarthRot = new SSISceneNodeAnimatorRotation(30, vector3df(0, 0.8f, 0), &IsActive);
	SSISceneNodeAnimatorFlyEllipce *animEarth = new SSISceneNodeAnimatorFlyEllipce(sun->getPosition(), 0, 7.25f, 100.0f, &koeffSpeed, 15.2f, 14.7f, &IsActive);
	if (earth)
	{
		earth->setMaterialFlag(EMF_LIGHTING, false);
		earth->setMaterialTexture(0, driver->getTexture(".\\data\\earth.png"));
		earth->addAnimator(animEarth);
		earth->addAnimator(animEarthRot);
	}
	return earth;
	//---------------------
}
