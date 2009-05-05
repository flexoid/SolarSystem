#include "SSPlanets.h"

ISceneNode* AddSun()
{
	ISceneNode *sun = smgr->addSphereSceneNode(150.0f, 64, 0, -1, vector3df(0, 0, 0), vector3df(0, 0, 0), vector3df(1.0, 1.0, 1.0));
	SSRotationAnimator *animSunRot = new SSRotationAnimator(vector3df(0, 5.0f / 30.0f, 0), &koeffSpeed, &IsActiveRotating);
	if (sun)
	{
		sun->setMaterialFlag(EMF_LIGHTING, false);
		sun->setMaterialTexture(0, driver->getTexture(".\\data\\suncyl1.jpg"));
		sun->addAnimator(animSunRot);
	}
	
	IBillboardSceneNode* SunFlame = smgr->addBillboardSceneNode(0, dimension2df(380.0, 380.0), vector3df(0, 0, 0));
	SunFlame->setMaterialFlag(EMF_LIGHTING, false);
	SunFlame->setMaterialType(EMT_TRANSPARENT_ALPHA_CHANNEL);

	array<ITexture*> textures;
	ITexture* t = driver->getTexture(".\\data\\1.png");
	textures.push_back(driver->getTexture(".\\data\\SynFlame1.png"));
	textures.push_back(driver->getTexture(".\\data\\SynFlame2.png"));
	textures.push_back(driver->getTexture(".\\data\\SynFlame3.png"));
	textures.push_back(driver->getTexture(".\\data\\SynFlame4.png"));
	ISceneNodeAnimator* SunFlameAnimator = smgr->createTextureAnimator(textures, 100);

	SunFlame->addAnimator(SunFlameAnimator);
	
	return sun;
}