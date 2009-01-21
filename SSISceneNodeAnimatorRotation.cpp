#include "SSISceneNodeAnimatorRotation.h"

SSISceneNodeAnimatorRotation::SSISceneNodeAnimatorRotation(u32 time, const core::vector3df& rotation, f32* koeffOfSpeed, bool *IsActive)
{
	this->rotation = rotation;
	this->StartTime = time;
	this->IsActive = IsActive;
	this->koeffOfSpeed = koeffOfSpeed;
}

SSISceneNodeAnimatorRotation::~SSISceneNodeAnimatorRotation()
{
}

void SSISceneNodeAnimatorRotation::animateNode(ISceneNode* node, u32 timeMs)
{
	if (node)
	{
		if (*IsActive)
		{
			u32 diffTime = timeMs - StartTime;

			if (diffTime != 0)
			{
				core::vector3df NewRotation = node->getRotation(); 
				NewRotation += rotation* ((diffTime)/10.0f) * *koeffOfSpeed; 
				node->setRotation(NewRotation); 
				StartTime=timeMs; 
			}
		} else StartTime=timeMs;
	}
}


void SSISceneNodeAnimatorRotation::serializeAttributes(io::IAttributes* out, io::SAttributeReadWriteOptions* options) const
{
	out->addVector3d("Rotation", rotation);
}


void SSISceneNodeAnimatorRotation::deserializeAttributes(io::IAttributes* in, io::SAttributeReadWriteOptions* options)
{
	rotation = in->getAttributeAsVector3d("Rotation");
}