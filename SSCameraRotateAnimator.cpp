#include "SSCameraRotateAnimator.h"
#include "SSMoveCameraTo.h"

extern bool CorrectPosFlag;

SSCameraRotateAnimator::SSCameraRotateAnimator(ICameraSceneNode* camera, vector3df FinalTarget, ISceneNode* TargetNode, f32 radius)
{
	this->FinalTarget = FinalTarget;
	this->TargetNode = TargetNode;
	this->radius = radius;
	this->camera = camera;
	this->koeff = 1;
}

SSCameraRotateAnimator::~SSCameraRotateAnimator(void)
{
}

void SSCameraRotateAnimator::animateNode(ISceneNode* node, u32 timeMs)
{
	f32 alpha = RADTODEG * acos((FinalTarget.X*camera->getTarget().X + FinalTarget.Y*camera->getTarget().Y + FinalTarget.Z*camera->getTarget().Z)
		/ sqrt ((FinalTarget.X*FinalTarget.X + FinalTarget.Y*FinalTarget.Y + FinalTarget.Z*FinalTarget.Z)
		* (camera->getTarget().X*camera->getTarget().X + camera->getTarget().Y*camera->getTarget().Y + camera->getTarget().Z*camera->getTarget().Z)));

	if (alpha > 30.0f) koeff = 2;
	else if (alpha > 80.0f) koeff = 4;
	
	if ((FinalTarget - camera->getTarget()).getLengthSQ() > 0.5f)
		camera->setTarget(camera->getTarget() + (FinalTarget - camera->getTarget()).normalize() * (f32)koeff);
	vector3df FinalPos = CalcFinalPos(TargetNode, radius);
	if (CorrectPosFlag)
	{
		camera->setPosition(FinalPos);
		camera->setTarget(TargetNode->getPosition());
	}
}

void SSCameraRotateAnimator::serializeAttributes(io::IAttributes* out, io::SAttributeReadWriteOptions* options) const
{
}

//! Reads attributes of the scene node animator.
void SSCameraRotateAnimator::deserializeAttributes(io::IAttributes* in, io::SAttributeReadWriteOptions* options)
{
}