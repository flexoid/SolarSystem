#include "SSPlanets.h"

ISceneNode* AddNeptune()
{
	ISceneNode *neptune = smgr->addSphereSceneNode(16.0f, 32, 0, -1, vector3df(0, 0, 0), vector3df(0, 0, 0), vector3df(1.0, 1.0, 1.0));
	SSRotationAnimator *animNeptuneRot = new SSRotationAnimator(vector3df(0, 5.0f / 0.63f, 0), &koeffSpeed, &IsActiveRotating);
	SSFlyEllipceAnimator *animNeptune = new SSFlyEllipceAnimator(sun->getPosition(), 0, 6.4f, 5.4f, &koeffSpeed, 1800.0f, 1750.0f, &koeffOfDist, &IsActiveMoving);
	if (neptune)
	{
		neptune->setMaterialFlag(EMF_LIGHTING, false);
		neptune->setMaterialTexture(0, driver->getTexture(std::string(TexturesPath + "Neptune/Neptune.jpg").c_str()));
		neptune->addAnimator(animNeptune);
		neptune->addAnimator(animNeptuneRot);
		neptune->setRotation(vector3df(0.0f, 29.0f, 29.0f));
	}

	Planets.push_back(neptune);

	return neptune;
}