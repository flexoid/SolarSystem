#include "SSPlanets.h"

ISceneNode* AddMars()
{
	ISceneNode *mars = smgr->addSphereSceneNode(2.0f, 32, 0, -1, vector3df(0, 0, 0), vector3df(0, 0, 0), vector3df(1.0, 1.0, 1.0));
	SSRotationAnimator *animMarsRot = new SSRotationAnimator(vector3df(0, 5.0f / 1.0f, 0), &koeffSpeed, &IsActiveRotating);
	SSFlyEllipceAnimator *animMars = new SSFlyEllipceAnimator(sun->getPosition(), 0, 5.65f, 24.1f, &koeffSpeed, 491.0f, 420.0f, &koeffOfDist, &IsActiveMoving);
	if (mars)
	{
		mars->setMaterialFlag(EMF_LIGHTING, false);
		mars->setMaterialTexture(0, driver->getTexture(std::string(PathToTextures + "Mars/Mars.jpg").c_str()));
		mars->addAnimator(animMars);
		mars->addAnimator(animMarsRot);
		mars->setRotation(vector3df(0.0f, 25.0f, 25.0f));
	}

	Planets.push_back(mars);

	return mars;
}
