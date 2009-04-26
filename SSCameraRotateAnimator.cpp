#include "SSCameraRotateAnimator.h"
#include "SSMoveCameraTo.h"

extern bool CorrectPosFlag;

SSCameraRotateAnimator::SSCameraRotateAnimator(ICameraSceneNode* camera, vector3df FinalTarget, ISceneNode* TargetNode, f32 radius)
{
	this->FinalTarget = FinalTarget;
	this->TargetNode = TargetNode;
	this->radius = radius;
	this->camera = camera;
}

SSCameraRotateAnimator::~SSCameraRotateAnimator(void)
{
}

void SSCameraRotateAnimator::animateNode(ISceneNode* node, u32 timeMs)
{
	if ((FinalTarget - camera->getTarget()).getLengthSQ() > 0.5f)
		camera->setTarget(camera->getTarget() + (FinalTarget - camera->getTarget()).normalize());
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