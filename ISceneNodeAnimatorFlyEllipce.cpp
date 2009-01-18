#include "ISceneNodeAnimatorFlyEllipce.h"

ISceneNodeAnimatorFlyEllipce::ISceneNodeAnimatorFlyEllipce(const core::vector3df& focus, f32 degrees, f32 speed, f32 afelij, f32 peregelij)
{
	Speed = speed;
	X_radius = afelij + peregelij;
	Y_radius = sqrtf(X_radius*X_radius - (afelij - peregelij)*(afelij - peregelij));
	deg = 0;
	Focus = focus;
	Center.X = Focus.X + ((afelij - peregelij)/2) * cosf(degrees*DEGTORAD);
	Center.Y = Focus.Y + ((afelij - peregelij)/2) * sinf(degrees*DEGTORAD);
}

void ISceneNodeAnimatorFlyEllipce::animateNode(ISceneNode* node, u32 timeMs)
{
	if (node)
	{
		u32 diffTime = timeMs - StartTime;
		if (diffTime != 0)
		{
			if (deg >= 360.0f) deg = 0;
			deg = deg + 1.0f / 1000.0f * diffTime * Speed;
			f32 rad = deg * DEGTORAD;
			vector3df newpos = node->getPosition();
			newpos.X = Center.X + X_radius * cosf(rad);
			newpos.Z = Center.Z + Y_radius * sinf(rad);
			node->setPosition(newpos);
			StartTime = timeMs;
		}
	}
}

ISceneNodeAnimatorFlyEllipce::~ISceneNodeAnimatorFlyEllipce(void)
{
}

void ISceneNodeAnimatorFlyEllipce::serializeAttributes(io::IAttributes* out, io::SAttributeReadWriteOptions* options) const
{
	//out->addVector3d("Rotation", Rotation);
}

//! Reads attributes of the scene node animator.
void ISceneNodeAnimatorFlyEllipce::deserializeAttributes(io::IAttributes* in, io::SAttributeReadWriteOptions* options)
{
	//Rotation = in->getAttributeAsVector3d("Rotation");
}
