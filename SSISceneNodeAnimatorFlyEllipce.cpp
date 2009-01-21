#include "SSISceneNodeAnimatorFlyEllipce.h"
#include <iostream>

SSISceneNodeAnimatorFlyEllipce::SSISceneNodeAnimatorFlyEllipce(const core::vector3df& focus, f32 rotateDeg, f32 orbDeg, f32 speed, f32* koeffOfSpeed, f32 afelij, f32 peregelij, bool *IsActive)
{
	Speed = speed;
	koeffSpeed = koeffOfSpeed;
	X_radius = (afelij + peregelij)/2;
	Y_radius = sqrtf(X_radius*X_radius - ((afelij - peregelij)/2)*((afelij - peregelij)/2));
	std::cout << X_radius << std::endl << Y_radius << std::endl;
	deg = 0;
	Focus = focus;
	Center.X = Focus.X + ((afelij - peregelij)/2);
	Active = IsActive;
	this->rotateDeg = rotateDeg;
	this->orbDeg = orbDeg;
}

void SSISceneNodeAnimatorFlyEllipce::animateNode(ISceneNode* node, u32 timeMs)
{
	if (node)
	{
		if (*Active)
		{
			u32 diffTime = timeMs - StartTime;
			if (diffTime != 0)
			{
				if (deg >= 360.0f && deg <= -360.0f) deg = 0;
				deg += 1.0f / 1000.0f * diffTime * Speed * *koeffSpeed;
				vector3df newpos = node->getPosition();
				newpos.X = Center.X + X_radius * cosf(deg * DEGTORAD);
				newpos.Z = Center.Z + Y_radius * sinf(deg * DEGTORAD);
				newpos.Y = Center.Y + X_radius * sinf(orbDeg * DEGTORAD) * sinf((deg + rotateDeg) * DEGTORAD);
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
