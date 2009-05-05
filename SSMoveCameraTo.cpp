#include "SSMoveCameraTo.h"
#include "SSCameraRotateAnimator.h"

bool CorrectPosFlag = false;
extern IVideoDriver* driver;
u32 x = 0;

u32 SSMoveCameraTo(ICameraSceneNode* CamToMove, ISceneNode* FinalNode, SSGUISideInfoBar* bar1, SSGUISideNavigateBar* bar2)
{
	IAttributes *attrib = device->getFileSystem()->createEmptyAttributes();
	FinalNode->serializeAttributes(attrib);
	f32 radius = attrib->getAttributeAsFloat("Radius");
	vector3df FinalPosition = CalcFinalPos(FinalNode, radius);
	ISceneNodeAnimator* animRot = new SSCameraRotateAnimator(CamToMove, FinalNode, radius);

	if (FinalNode->getPosition() != vector3df(0,0,0)) bar2->hide();
	else bar2->show();
	for (; x < 255; x++) Sleep(3);
	CamToMove->removeAnimators();
	CamToMove->addAnimator(animRot);
	CamToMove->setPosition(FinalPosition);
	if (FinalNode->getPosition() != vector3df(0,0,0)) bar1->show();
	else bar2->hide();
	for (; x > 0; x--) Sleep(3);

	return 3000;
}

vector3df CalcFinalPos(ISceneNode* node, f32 length)
{
	vector3df FinalPos;
	if (node->getPosition() != vector3df(0,0,0))
	{
		vector3df pos = node->getPosition();
		f32 a = sqrtf(pos.X*pos.X + pos.Z*pos.Z);
		f32 cosA = pos.X / a;
		f32 sinA = pos.Z / a;
		FinalPos.X = (a + length * 4) * cosA;
		FinalPos.Z = (a + length * 4) * sinA;
		FinalPos.Y = pos.Y + length;
	}
	else
	{
		FinalPos.X = length * 4;
		FinalPos.Z = length * 4;
		FinalPos.Y = length;
	}
	return FinalPos;
}

void MovingCamera()
{
	if (x)
		driver->draw2DRectangle(SColor(x, 255, 255, 255), rect<s32>(position2d<s32>(0,0), driver->getScreenSize()));
}