#include "SSISceneNodeAnimatorFlyEllipce.h"
#include <iostream>

SSISceneNodeAnimatorFlyEllipce::SSISceneNodeAnimatorFlyEllipce(const core::vector3df& focus, f32 rotateDeg, f32 orbDeg, f32 speed, f32* koeffOfSpeed, f32 afelij, f32 peregelij, bool *IsActive)
{
	this->speed = speed;
	this->koeffOfSpeed = koeffOfSpeed;
	X_radius = (afelij + peregelij)/2;
	Y_radius = sqrtf(X_radius*X_radius - ((afelij - peregelij)/2)*((afelij - peregelij)/2));
	std::cout << X_radius << std::endl << Y_radius << std::endl;
	deg = 0;
	this->focus = focus;
	center.X = focus.X + ((afelij - peregelij)/2);
	this->IsActive = IsActive;
	this->rotateDeg = rotateDeg;
	this->orbDeg = orbDeg;
}

void SSISceneNodeAnimatorFlyEllipce::animateNode(ISceneNode* node, u32 timeMs)
{
	if (node)
	{
		if (*IsActive)
		{
			u32 diffTime = timeMs - StartTime;
			if (diffTime != 0)
			{
				if (deg >= 360.0f && deg <= -360.0f) deg = 0;
				deg += 1.0f / 1000.0f * diffTime * speed * *koeffOfSpeed;
				vector3df newpos = node->getPosition();
				newpos.X = center.X + X_radius * cosf(deg * DEGTORAD);
				newpos.Z = center.Z + Y_radius * sinf(deg * DEGTORAD);
				newpos.Y = center.Y + X_radius * sinf(orbDeg * DEGTORAD) * sinf((deg + rotateDeg) * DEGTORAD);
				node->setPosition(newpos);
				StartTime = timeMs;
			}
		}
		else StartTime = timeMs;
	}
}

SSISceneNodeAnimatorFlyEllipce::~SSISceneNodeAnimatorFlyEllipce(void)
{
}

void SSISceneNodeAnimatorFlyEllipce::serializeAttributes(io::IAttributes* out, io::SAttributeReadWriteOptions* options) const
{
	//out->addVector3d("Rotation", Rotation);
}

//! Reads attributes of the scene node animator.
void SSISceneNodeAnimatorFlyEllipce::deserializeAttributes(io::IAttributes* in, io::SAttributeReadWriteOptions* options)
{
	//Rotation = in->getAttributeAsVector3d("Rotation");
}
