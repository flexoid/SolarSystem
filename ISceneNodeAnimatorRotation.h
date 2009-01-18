//  Класс, схожий со стандартным классом СSceneNodeAnimatorRotation
//за исключением возможности остановить анимацию установкой параметра IsActive в false.

#pragma once
#include <irrlicht.h>

#ifndef __I_SCENE_NODE_ANIMATOR_ROTATION_H_INCLUDED__
#define __I_SCENE_NODE_ANIMATOR_ROTATION_H_INCLUDED__

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

class ISceneNodeAnimatorRotation : public ISceneNodeAnimator
{

public:
	ISceneNodeAnimatorRotation(u32 time, const core::vector3df& rotation, bool *IsActive);
	virtual ~ISceneNodeAnimatorRotation();
	virtual void animateNode(ISceneNode* node, u32 timeMs);
	virtual void serializeAttributes(io::IAttributes* out, io::SAttributeReadWriteOptions* options=0) const;
	virtual void deserializeAttributes(io::IAttributes* in, io::SAttributeReadWriteOptions* options=0);
	virtual ESCENE_NODE_ANIMATOR_TYPE getType() const { return ESNAT_ROTATION; }

private:
	core::vector3df Rotation;
	u32 StartTime;
	bool *Active;

};

#endif