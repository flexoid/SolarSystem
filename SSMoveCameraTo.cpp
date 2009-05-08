#include "SSMoveCameraTo.h"
#include "SSCameraRotateAnimator.h"
#include "SSGUI.h"

bool CorrectPosFlag = false;
extern IVideoDriver* driver;
u32 x = 0;

ICameraSceneNode* CamToMove;
ISceneNode* FinalNode;
extern ICameraSceneNode* camera;

void t1()
{
	IAttributes *attrib = device->getFileSystem()->createEmptyAttributes();
	FinalNode->serializeAttributes(attrib);
	f32 radius = attrib->getAttributeAsFloat("Radius");
	vector3df FinalPosition = CalcFinalPos(FinalNode, radius);
	ISceneNodeAnimator* animRot = new SSCameraRotateAnimator(CamToMove, FinalNode, radius);

	SideNavigateBar->hide();
	Sleep(300);
	for (x = 0; x < 255; x++) Sleep(4);
	ZoomScrollBar->setVisible(true);
	DistanceScrollBar->setVisible(false);
	CamToMove->removeAnimators();
	CamToMove->addAnimator(animRot);
	CamToMove->setPosition(FinalPosition);
	FillSideInfoBar(currentPlanetID);
	for (x = 255; x > 0; x--) Sleep(4);
	SideInfoBar->show();
}

void t2()
{
	SideInfoBar->hide();
	Sleep(1000);
	for (x = 0; x < 255; x++) Sleep(4);
	ZoomScrollBar->setVisible(false);
	DistanceScrollBar->setVisible(true);
	ZoomScrollBar->setPos(ZoomScrollBar->getMax() / 2);
	camera->removeAnimators();
	camera->setPosition(vector3df(-1000.0f, 500.0f, -1000.0f));
	camera->setTarget(vector3df(0,0,0));
	for (x = 255; x > 0; x--) Sleep(4);
	SideNavigateBar->show();
}

HANDLE thread1;
DWORD threadId1;

void SSMoveCameraTo(ICameraSceneNode* CamToMove, ISceneNode* FinalNode)
{
	::CamToMove = CamToMove;
	::FinalNode = FinalNode;
	if (thread1)
	{
		GetExitCodeThread(thread1, &threadId1);
		TerminateThread(thread1, threadId1);
		thread1 = 0;
	}
	thread1 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)t1, NULL, 0, &threadId1);
	return;
}

void SSCameraStartPos(ICameraSceneNode* CamToMove)
{
	if (thread1)
	{
		GetExitCodeThread(thread1, &threadId1);
		TerminateThread(thread1, threadId1);
		thread1 = 0;
	}
	thread1 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)t2, NULL, 0, &threadId1);
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
		FinalPos.X = (a + length * 8) * cosA;
		FinalPos.Z = (a + length * 8) * sinA;
		FinalPos.Y = pos.Y + length * 2;
	}
	else
	{
		FinalPos.X = length * 8;
		FinalPos.Z = length * 8;
		FinalPos.Y = length * 2;
	}
	return FinalPos;
}

void MovingCamera()
{
	if (x)
		driver->draw2DRectangle(SColor(x, 0, 0, 0), rect<s32>(position2d<s32>(0,0), driver->getScreenSize()));
}