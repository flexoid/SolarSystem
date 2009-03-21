#include "SSPlanets.h"

ISceneNode* AddEarth()
{
	//---------Демонстрация
	ISceneNode *earth = smgr->addSphereSceneNode(10.0, 32, 0, -1, vector3df(10, 0, 0), vector3df(0, 0, 0), vector3df(1.0, 1.0, 1.0));
	SSISceneNodeAnimatorRotation *animEarthRot = new SSISceneNodeAnimatorRotation(vector3df(0, 0.8f, 0), &koeffSpeed, &IsActiveRotating);
	SSISceneNodeAnimatorFlyEllipce *animEarth = new SSISceneNodeAnimatorFlyEllipce(sun->getPosition(), 0, 7.25f, 100.0f, &koeffSpeed, 304.0f, 294.0f, &IsActiveMoving);
	if (earth)
	{
		earth->setMaterialFlag(EMF_LIGHTING, false);
		earth->setMaterialTexture(0, driver->getTexture(".\\data\\EarthMap_2500x1250_2.jpg"));
		earth->addAnimator(animEarth);
		earth->addAnimator(animEarthRot);
	}
	return earth;
	//---------------------
}
