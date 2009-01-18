#include "SSISceneNodeAnimatorRotation.h"

SSISceneNodeAnimatorRotation::SSISceneNodeAnimatorRotation(u32 time, const core::vector3df& rotation, bool *IsActive)
{
	Rotation = rotation;
	StartTime = time;
	Active = IsActive;
}

SSISceneNodeAnimatorRotation::~SSISceneNodeAnimatorRotation()
{
}

void SSISceneNodeAnimatorRotation::animateNode(ISceneNode* node, u32 timeMs)
{
	if (node)
	{
		if (*Active)
		{
			u32 diffTime = timeMs - StartTime;

			if (diffTime != 0)
			{
				core::vector3df NewRotation = node->getRotation(); 
				NewRotation += Rotation* ((diffTime)/10.0f); 
				node->setRotation(NewRotation); 
				StartTime=timeMs; 
			}
		} else StartTime=timeMs;
	}
}


void SSISceneNodeAnimatorRotation::serializeAttributes(io::IAttributes* out, io::SAttributeReadWriteOptions* options) const
{
	out->addVector3d("Rotation", Rotation);
}


void SSISceneNodeAnimatorRotation::deserializeAttributes(io::IAttributes* in, io::SAttributeReadWriteOptions* options)
{
	Rotation = in->getAttributeAsVector3d("Rotation");
}