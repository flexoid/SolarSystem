#include "SSPlanets.h"

ISceneNode* AddSaturn()
{
	ISceneNode *saturn = smgr->addSphereSceneNode(38.0f, 32, 0, -1, vector3df(0, 0, 0), vector3df(0, 0, 0), vector3df(1.0, 1.0, 1.0));
	SSRotationAnimator *animSaturnRot = new SSRotationAnimator(vector3df(0, 5.0f / 0.4f, 0), &koeffSpeed, &IsActiveRotating);
	SSFlyEllipceAnimator *animSaturn = new SSFlyEllipceAnimator(sun->getPosition(), 0, 5.51f, 9.7f, &koeffSpeed, 1000.0f, 850.0f, &koeffOfDist, &IsActiveMoving);
	if (saturn)
	{
		saturn->setMaterialFlag(EMF_LIGHTING, false);
		saturn->setMaterialTexture(0, driver->getTexture(std::string(PathToTextures + "Saturn/Saturn.jpg").c_str()));
		saturn->addAnimator(animSaturn);
		saturn->addAnimator(animSaturnRot);
		saturn->setRotation(vector3df(0.0f, 26.0f, 26.0f));
	}
	ISceneNode *saturnRings = smgr->addMeshSceneNode(smgr->getMesh("./data/Models/SaturnRings/SaturnRings.obj"), saturn);
	saturnRings->setMaterialFlag(EMF_LIGHTING, false);
	saturnRings->setScale(vector3df(2.0f, 2.0f, 2.0f));
	saturnRings->setMaterialTexture(0, driver->getTexture(std::string(PathToTextures + "Saturn/SaturnRings.png").c_str()));
	saturnRings->setMaterialType(EMT_TRANSPARENT_ALPHA_CHANNEL);

	Planets.push_back(saturn);

	return saturn;
}
