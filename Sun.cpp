#include "SSPlanets.h"

ISceneNode* AddSun()
{
	//---------Демонстрация
	ISceneNode *sun = smgr->addSphereSceneNode(100.0, 64, 0, -1, vector3df(0, 0, 0), vector3df(0, 0, 0), vector3df(1.0, 1.0, 1.0));
	SSRotationAnimator *animSunRot = new SSRotationAnimator(vector3df(0, -0.8f, 0), &koeffSpeed, &IsActiveRotating);
	if (sun)
	{
		sun->setMaterialFlag(EMF_LIGHTING, false);
		sun->setMaterialTexture(0, driver->getTexture(".\\data\\suncyl1.jpg"));
		sun->addAnimator(animSunRot);
	}
	return sun;
	//---------------------
}