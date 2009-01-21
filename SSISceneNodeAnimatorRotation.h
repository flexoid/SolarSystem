//  Класс, схожий со стандартным классом СSceneNodeAnimatorRotation
//за исключением возможности остановить анимацию установкой параметра IsActive в false.

#include <irrlicht.h>

#ifndef __SS_I_SCENE_NODE_ANIMATOR_ROTATION_H_INCLUDED__
#define __SS_I_SCENE_NODE_ANIMATOR_ROTATION_H_INCLUDED__

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

class SSISceneNodeAnimatorRotation : public ISceneNodeAnimator
{

public:
	SSISceneNodeAnimatorRotation(u32 time, const core::vector3df& rotation, f32* koeffOfSpeed, bool *IsActive);
	virtual ~SSISceneNodeAnimatorRotation();
	virtual void animateNode(ISceneNode* node, u32 timeMs);
	virtual void serializeAttributes(io::IAttributes* out, io::SAttributeReadWriteOptions* options=0) const;
	virtual void deserializeAttributes(io::IAttributes* in, io::SAttributeReadWriteOptions* options=0);
	virtual ESCENE_NODE_ANIMATOR_TYPE getType() const { return ESNAT_ROTATION; }

private:
	core::vector3df rotation;
	u32 StartTime;
	bool *IsActive;
	f32 *koeffOfSpeed;

};

#endif