//  Класс-аниматор для задания телу движения по эллиптической траектории
//с возможностью остановить анимацию установкой параметра IsActive в false.

#pragma once
#include <irrlicht.h>

#ifndef __C_SCENE_NODE_ANIMATOR_FLY_ELLIPCE_H_INCLUDED__
#define __C_SCENE_NODE_ANIMATOR_FLY_ELLIPCE_H_INCLUDED__

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

class ISceneNodeAnimatorFlyEllipce : public ISceneNodeAnimator
{
public:
	ISceneNodeAnimatorFlyEllipce(const core::vector3df& focus, f32 degrees, f32 speed, f32 afelij, f32 peregelij, bool *IsActive);
	~ISceneNodeAnimatorFlyEllipce(void);
	virtual void animateNode(ISceneNode* node, u32 timeMs);
	virtual void serializeAttributes(io::IAttributes* out, io::SAttributeReadWriteOptions* options=0) const;
	virtual void deserializeAttributes(io::IAttributes* in, io::SAttributeReadWriteOptions* options=0);
	virtual ESCENE_NODE_ANIMATOR_TYPE getType() const { return ESNAT_FLY_CIRCLE; }

private:
	u32 StartTime;
	f32 X_radius;
	f32 Y_radius;
	f32 Speed;
	f32 deg;
	core::vector3df Focus;
	core::vector3df Center;
	bool *Active;
};

#endif