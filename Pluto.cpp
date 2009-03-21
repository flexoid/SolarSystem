#include "SSPlanets.h"

ISceneNode* AddPluto()
{
	//---------Демонстрация
	ISceneNode *pluto = smgr->addSphereSceneNode(2.5f, 16, 0, -1, vector3df(10, 0, 0), vector3df(0, 0, 0), vector3df(1.0, 1.0, 1.0));
	SSISceneNodeAnimatorRotation *animPlutoRot = new SSISceneNodeAnimatorRotation(vector3df(0, 0.8f, 0), &koeffSpeed, &IsActiveRotating);
	SSISceneNodeAnimatorFlyEllipce *animPluto = new SSISceneNodeAnimatorFlyEllipce(sun->getPosition(), 0, 11.3f, 50.0f, &koeffSpeed, 738.0f, 444.0f, &IsActiveMoving);
	if (pluto)
	{
		pluto->setMaterialFlag(EMF_LIGHTING, false);
		pluto->setMaterialTexture(0, driver->getTexture(".\\data\\pluto.png"));
		pluto->addAnimator(animPluto);
		pluto->addAnimator(animPlutoRot);
	}
	return pluto;
	//---------------------
}
