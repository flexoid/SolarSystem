//  Класс-аниматор для задания телу движения по эллиптической траектории
//с возможностью остановить анимацию установкой параметра IsActive в false.

#include <irrlicht.h>

#ifndef __SS_I_SCENE_NODE_ANIMATOR_FLY_ELLIPCE_H_INCLUDED__
#define __SS_I_SCENE_NODE_ANIMATOR_FLY_ELLIPCE_H_INCLUDED__

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

extern IVideoDriver* driver;

class SSISceneNodeAnimatorFlyEllipce : public ISceneNodeAnimator
{
public:
	SSISceneNodeAnimatorFlyEllipce::SSISceneNodeAnimatorFlyEllipce(const core::vector3df& focus, f32 rotateDeg, f32 orbDeg, f32 speed, f32* koeffOfSpeed, f32 afelij, f32 peregelij, bool *IsActive);
	~SSISceneNodeAnimatorFlyEllipce(void);
	virtual void animateNode(ISceneNode* node, u32 timeMs);
	virtual void serializeAttributes(io::IAttributes* out, io::SAttributeReadWriteOptions* options=0) const;
	virtual void deserializeAttributes(io::IAttributes* in, io::SAttributeReadWriteOptions* options=0);
	virtual ESCENE_NODE_ANIMATOR_TYPE getType() const { return ESNAT_FLY_CIRCLE; }

private:
	u32 StartTime;
	f32 X_radius;
	f32 Y_radius;
	f32 speed;
	f32 *koeffOfSpeed;
	f32 deg;
	f32 rotateDeg;
	f32 orbDeg;
	core::vector3df focus;
	core::vector3df center;
	bool *IsActive;
	f32 afelij, peregelij;
};

#endif