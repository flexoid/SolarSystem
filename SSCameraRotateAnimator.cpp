#include "SSCameraRotateAnimator.h"
#include "SSMoveCameraTo.h"

extern bool CorrectPosFlag;

SSCameraRotateAnimator::SSCameraRotateAnimator(ICameraSceneNode* camera, ISceneNode* TargetNode, f32 length)
{
	this->camera = camera;
	this->TargetNode = TargetNode;
	this->length = length;
}

SSCameraRotateAnimator::~SSCameraRotateAnimator(void)
{
}

void SSCameraRotateAnimator::animateNode(ISceneNode* node, u32 timeMs)
{
	camera->setPosition(CalcFinalPos(TargetNode, length));
	camera->setTarget(TargetNode->getPosition());
}

void SSCameraRotateAnimator::serializeAttributes(io::IAttributes* out, io::SAttributeReadWriteOptions* options) const
{
}

//! Reads attributes of the scene node animator.
void SSCameraRotateAnimator::deserializeAttributes(io::IAttributes* in, io::SAttributeReadWriteOptions* options)
{
}