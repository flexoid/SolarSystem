#include "SSMoveCameraTo.h"
#include "SSCameraRotateAnimator.h"

bool startAnimFlag = false;
bool checkFlag = false;
vector3df StartPosition;
vector3df FinalPosition;
vector3df MoveVector;
vector3df FinalTarget;
vector3df StartTarget;
ICameraSceneNode *CamToMove;
u32 TimeForWay;
ISceneNode* FinalNode = 0;
f32 radius;
HANDLE CamMutex;
bool CorrectPosFlag = false;

SSCameraRotateAnimator* animRot;
ISceneNodeAnimator* animMove;

u32 SSMoveCameraTo(ICameraSceneNode* CamToMove, ISceneNode* FinalNode)
{
	CamMutex = CreateMutex (NULL, FALSE, NULL);
	WaitForSingleObject(CamMutex, INFINITE);
	CamToMove->removeAnimators();
	IsActiveMoving = false;
	startAnimFlag = true;
	checkFlag = true;
	CorrectPosFlag = false;
	::CamToMove = CamToMove;
	IAttributes *attrib = device->getFileSystem()->createEmptyAttributes();
	FinalNode->serializeAttributes(attrib);
	radius = attrib->getAttributeAsFloat("Radius");
	::FinalPosition = CalcFinalPos(FinalNode, radius);
	::FinalTarget = FinalNode->getPosition();
	if (abs((FinalPosition - CamToMove->getPosition()).getLength())*10 < 10000)
		::TimeForWay = abs((FinalPosition - CamToMove->getPosition()).getLength())*10;
	else ::TimeForWay = 15000;
	::FinalNode = FinalNode;
	ReleaseMutex(CamMutex);
	return ::TimeForWay;
}

vector3df CalcFinalPos(ISceneNode* node, f32 length)
{
	vector3df pos = node->getPosition();
	vector3df FinalPos;
	if (pos != vector3df(0,0,0))
	{
		f32 a = sqrtf(pos.X*pos.X + pos.Z*pos.Z);
		f32 cosA = pos.X / a;
		f32 sinA = pos.Z / a;
		FinalPos.X = (a + length * 4) * cosA;
		FinalPos.Z = (a + length * 4) * sinA;
		FinalPos.Y = pos.Y + length;
	}
	else
	{
		FinalPos.X = length * 2;
		FinalPos.Y = length;
		FinalPos.Z = length * 2;
	}
	return FinalPos;
}

void MovingCamera(void)
{
	WaitForSingleObject(CamMutex, INFINITE);
	if (startAnimFlag)
	{
		animRot = new SSCameraRotateAnimator(CamToMove, FinalTarget, FinalNode, radius);
		animMove = smgr->createFlyStraightAnimator(CamToMove->getPosition(), FinalPosition, TimeForWay);
		CamToMove->addAnimator(animRot);
		CamToMove->addAnimator(animMove);
		startAnimFlag = false;
	}

	else if(checkFlag)
	{
		if ((CamToMove->getPosition() - FinalPosition).getLengthSQ() < 0.1f)
		{
			CorrectPosFlag = true;
			IsActiveMoving = true;
			checkFlag = false;
			CamToMove->removeAnimator(animMove);
		}
	}
	ReleaseMutex(CamMutex);
}