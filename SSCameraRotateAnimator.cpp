#include "SSCameraRotateAnimator.h"
#include "SSMoveCameraTo.h"

s32 koeffOfScale;
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
	camera->setPosition(TargetNode->getPosition().getInterpolated(CalcFinalPos(TargetNode, length), (f32)koeffOfScale / 10000.0f));
	camera->setTarget(TargetNode->getPosition());
}

void SSCameraRotateAnimator::serializeAttributes(io::IAttributes* out, io::SAttributeReadWriteOptions* options) const
{
}

//! Reads attributes of the scene node animator.
void SSCameraRotateAnimator::deserializeAttributes(io::IAttributes* in, io::SAttributeReadWriteOptions* options)
{
}