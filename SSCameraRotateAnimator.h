#pragma once
#include <irrlicht.h>

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

class SSCameraRotateAnimator : public ISceneNodeAnimator
{
public:
	SSCameraRotateAnimator(ICameraSceneNode* camera, vector3df FinalTarget, ISceneNode* TargetNode, f32 radius);
	virtual ~SSCameraRotateAnimator();
	virtual void animateNode(ISceneNode* node, u32 timeMs);
	virtual void serializeAttributes(io::IAttributes* out, io::SAttributeReadWriteOptions* options=0) const;
	virtual void deserializeAttributes(io::IAttributes* in, io::SAttributeReadWriteOptions* options=0);
	virtual ESCENE_NODE_ANIMATOR_TYPE getType() const { return ESNAT_UNKNOWN; }
private:
	vector3df FinalTarget;
	ISceneNode* TargetNode;
	f32 radius;
	ICameraSceneNode* camera;
	int koeff;
};
