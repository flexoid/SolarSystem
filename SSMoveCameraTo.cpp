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

void SSMoveCameraTo(ICameraSceneNode* CamToMove, ISceneNode* FinalNode, u32 TimeForWay)
{
	CamMutex = CreateMutex (NULL, FALSE, NULL);
	WaitForSingleObject(CamMutex, INFINITE);
	CamToMove->removeAnimators();
	IsActiveMoving = false;
	IsActiveRotating = false;
	startAnimFlag = true;
	checkFlag = true;
	CorrectPosFlag = false;
	::CamToMove = CamToMove;
	IAttributes *attrib = device->getFileSystem()->createEmptyAttributes();
	FinalNode->serializeAttributes(attrib);
	radius = attrib->getAttributeAsFloat("Radius");
	::FinalPosition = CalcFinalPos(FinalNode, radius);
	::FinalTarget = FinalNode->getPosition();
	::TimeForWay = TimeForWay;
	::FinalNode = FinalNode;
	ReleaseMutex(CamMutex);
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
		FinalPos.X = (a + length * 2) * cosA;
		FinalPos.Z = (a + length * 2) * sinA;
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
		if ((CamToMove->getPosition() - FinalPosition).getLengthSQ() < 1.0f)
		{
			CorrectPosFlag = true;
			IsActiveMoving = true;
			IsActiveRotating = true;
			checkFlag = false;
			CamToMove->removeAnimator(animMove);
		}
	}
	ReleaseMutex(CamMutex);
}