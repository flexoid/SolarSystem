#include "SSPlanets.h"

ISceneNode *sun;

ISceneNode* AddSun()
{
	//---------Демонстрация
	sun = smgr->addSphereSceneNode(8.0, 16, 0, -1, vector3df(10, 0, 0), vector3df(0, 0, 0), vector3df(1.0, 1.0, 1.0));
	SSISceneNodeAnimatorRotation *animSunRot = new SSISceneNodeAnimatorRotation(30, vector3df(0, 0.8f, 0), &IsActive);
	if (sun)
	{
		sun->setMaterialFlag(EMF_LIGHTING, false);
		sun->setMaterialTexture(0, driver->getTexture(".\\data\\sun.png"));
		sun->addAnimator(animSunRot);
	}
	return sun;
	//---------------------
}