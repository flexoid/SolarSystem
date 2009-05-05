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
	SSCameraRotateAnimator(ICameraSceneNode* camera, ISceneNode* TargetNode, f32 length);
	virtual ~SSCameraRotateAnimator();
	virtual void animateNode(ISceneNode* node, u32 timeMs);
	virtual void serializeAttributes(io::IAttributes* out, io::SAttributeReadWriteOptions* options=0) const;
	virtual void deserializeAttributes(io::IAttributes* in, io::SAttributeReadWriteOptions* options=0);
	virtual ESCENE_NODE_ANIMATOR_TYPE getType() const { return ESNAT_UNKNOWN; }
private:
	ICameraSceneNode* camera;
	ISceneNode* TargetNode;
	f32 length;
};
