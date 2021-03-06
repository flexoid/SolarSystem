#include "SSPlanets.h"

array<ISceneNode*> Planets;

ISceneNode* AddSun()
{
	ISceneNode *sun = smgr->addSphereSceneNode(150.0f, 64, 0, -1, vector3df(0, 0, 0), vector3df(0, 0, 0), vector3df(1.0, 1.0, 1.0));
	SSRotationAnimator *animSunRot = new SSRotationAnimator(vector3df(0, 5.0f / 30.0f, 0), &koeffSpeed, &IsActiveRotating);
	if (sun)
	{
		sun->setMaterialFlag(EMF_LIGHTING, false);
		sun->setMaterialTexture(0, driver->getTexture(std::string(TexturesPath + "Sun/Sun.jpg").c_str()));
		sun->addAnimator(animSunRot);
	}
	
	IBillboardSceneNode* SunFlame = smgr->addBillboardSceneNode(0, dimension2df(360.0, 360.0), vector3df(0, 0, 0));
	SunFlame->setMaterialFlag(EMF_LIGHTING, false);
	SunFlame->setMaterialType(EMT_TRANSPARENT_ALPHA_CHANNEL);

	array<ITexture*> textures;
	textures.push_back(driver->getTexture(std::string(TexturesPath + "Sun/Flame/SynFlame1.png").c_str()));
	textures.push_back(driver->getTexture(std::string(TexturesPath + "Sun/Flame/SynFlame2.png").c_str()));
	textures.push_back(driver->getTexture(std::string(TexturesPath + "Sun/Flame/SynFlame3.png").c_str()));
	textures.push_back(driver->getTexture(std::string(TexturesPath + "Sun/Flame/SynFlame4.png").c_str()));
	ISceneNodeAnimator* SunFlameAnimator = smgr->createTextureAnimator(textures, 100);

	SunFlame->addAnimator(SunFlameAnimator);

	Planets.push_back(sun);
	
	return sun;
}