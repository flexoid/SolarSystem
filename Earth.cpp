#include "SSPlanets.h"

ISceneNode* AddEarth()
{
	ISceneNode *earth = smgr->addSphereSceneNode(4.0f, 32, 0, -1, vector3df(0, 0, 0), vector3df(0, 0, 0), vector3df(1.0, 1.0, 1.0));
	SSRotationAnimator *animEarthRot = new SSRotationAnimator(vector3df(0, 5.0f / 1.0f, 0), &koeffSpeed, &IsActiveRotating);
	SSFlyEllipceAnimator *animEarth = new SSFlyEllipceAnimator(sun->getPosition(), 0, 7.25f, 29.0f, &koeffSpeed, 300.0f, 280.0f, &koeffOfDist, &IsActiveMoving);
	if (earth)
	{
		earth->setMaterialFlag(EMF_LIGHTING, false);
		earth->setMaterialTexture(0, driver->getTexture(std::string(TexturesPath + "Earth/Earth.png").c_str()));
		earth->addAnimator(animEarth);
		earth->addAnimator(animEarthRot);
		earth->setRotation(vector3df(0.0f, 23.0f, 23.0f));
	}

	Planets.push_back(earth);

	return earth;
}