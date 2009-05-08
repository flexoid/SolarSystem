#include "SSFlyEllipceAnimator.h"
#include <iostream>

SSFlyEllipceAnimator::SSFlyEllipceAnimator(const core::vector3df& focus, f32 rotateDeg, f32 orbDeg, f32 speed, f32* koeffOfSpeed, f32 afelij, f32 peregelij, f32* koeffOfDist, bool *IsActive)
{
	this->speed = speed;
	this->koeffOfSpeed = koeffOfSpeed;
	this->afelij = afelij;
	this->peregelij = peregelij;
	this->koeffOfDist = koeffOfDist;
	deg = (f32)(rand() % 720 - 360);
	this->focus = focus;
	this->IsActive = IsActive;
	this->rotateDeg = rotateDeg;
	this->orbDeg = orbDeg;
	this->StartTime = 0;
}

void SSFlyEllipceAnimator::animateNode(ISceneNode* node, u32 timeMs)
{
	if (StartTime == 0) StartTime = timeMs;
	if (node)
	{
		if (*IsActive)
		{
			X_radius = (*koeffOfDist * afelij + *koeffOfDist * peregelij)/2;
			Y_radius = sqrtf(X_radius*X_radius - ((*koeffOfDist * afelij - *koeffOfDist * peregelij)/2)*((*koeffOfDist * afelij - *koeffOfDist * peregelij)/2));

			u32 diffTime = timeMs - StartTime;
			if (diffTime != 0)
			{
				center.X = focus.X + ((*koeffOfDist * afelij - *koeffOfDist * peregelij)/2);
				if (deg >= 360.0f && deg <= -360.0f) deg = 0;
				deg += 1.0f / 1000.0f * diffTime * speed * *koeffOfSpeed * -1;
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

SSFlyEllipceAnimator::~SSFlyEllipceAnimator(void)
{
}

void SSFlyEllipceAnimator::serializeAttributes(io::IAttributes* out, io::SAttributeReadWriteOptions* options) const
{
	//out->addVector3d("Rotation", Rotation);
}

//! Reads attributes of the scene node animator.
void SSFlyEllipceAnimator::deserializeAttributes(io::IAttributes* in, io::SAttributeReadWriteOptions* options)
{
	//Rotation = in->getAttributeAsVector3d("Rotation");
}
