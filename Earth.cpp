#include "Planets.h"

ISceneNode* AddEarth(IVideoDriver* driver, ISceneManager* smgr)
{
	//---------Демонстрация
	ISceneNode *earth = smgr->addSphereSceneNode(1.0, 16, 0, -1, vector3df(10, 0, 0), vector3df(0, 0, 0), vector3df(1.0, 1.0, 1.0));
	ISceneNodeAnimatorRotation *animEarthRot = new ISceneNodeAnimatorRotation(30, vector3df(0, 0.8f, 0), &IsActive);
	ISceneNodeAnimatorFlyEllipce *animEarth = new ISceneNodeAnimatorFlyEllipce(vector3df(0, 0, 0), 0, &speed, 15.2f, 14.7f, &IsActive);
	if (earth)
	{
		earth->setMaterialFlag(EMF_LIGHTING, false);
		earth->setMaterialTexture(0, driver->getTexture(".\\data\\earth.bmp"));
		earth->addAnimator(animEarth);
		earth->addAnimator(animEarthRot);
	}
	return earth;
	//---------------------
}
