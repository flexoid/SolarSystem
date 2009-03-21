#include "SSMoveCameraTo.h"
#include <iostream>

ICameraSceneNode* cam;
vector3df endPos;
vector3df target;
vector3df startPos;

bool doRotating = false;

DWORD WINAPI Rotating(void* arg);
DWORD WINAPI Moving(void* arg);
DWORD WINAPI Temp(void* arg);

void SSMoveCameraTo(ICameraSceneNode* cam, const core::vector3df& endPos, const core::vector3df& target)
{
	::cam = cam;
	::endPos = endPos;
	::target = target;
	DWORD threadId; // Идентификатор потока
	doRotating = true;
	HANDLE thread1 = CreateThread(NULL, 0, Moving, NULL, 0, &threadId);
	//HANDLE thread2 = CreateThread(NULL, 0, Rotating, NULL, 0, &threadId);
	HANDLE thread3 = CreateThread(NULL, 0, Temp, NULL, 0, &threadId);
}

DWORD WINAPI Rotating(void* arg)
{
	Beep(500, 100);
	f32 k = 0;
	f32 alpha_full = 1.0f;
	f32 alpha;

	while(1)
	{
		WaitForSingleObject(mutex, INFINITE);

		vector3df tmp1 = cam->getTarget() - cam->getPosition();
		vector3df tmp2 = endPos - cam->getPosition();

		alpha_full = acosf((tmp1.dotProduct(tmp2)) / 
			(tmp1.getLength() * tmp2.getLength()));

		if (alpha_full > 0.001f)
		{
			alpha = 0.0005f;

			cout << alpha_full << endl;

			k = 0.01f;
			vector3df rotVec = tmp1.crossProduct(tmp2);
			rotVec.normalize();

			f32 rotMatrix[3][3] =
			{
				{ cosf(alpha) + (1 - cosf(alpha)) * powf(rotVec.X, 2),
				(1 - cosf(alpha)) * rotVec.X * rotVec.Y - sinf(alpha) * rotVec.Z,
				(1 - cosf(alpha)) * rotVec.X * rotVec.Z + sinf(alpha) * rotVec.Y },

				{ (1 - cosf(alpha)) * rotVec.Y * rotVec.X + sinf(alpha) * rotVec.Z,
				cosf(alpha) + (1 - cosf(alpha)) * powf(rotVec.Y, 2),
				(1 - cosf(alpha)) * rotVec.Y * rotVec.Z - sinf(alpha) * rotVec.X },

				{ (1 - cosf(alpha)) * rotVec.Z * rotVec.X - sinf(alpha) * rotVec.Y,
				(1 - cosf(alpha)) * rotVec.Z * rotVec.Y + sinf(alpha) * rotVec.X,
				cosf(alpha) + (1 - cosf(alpha)) * powf(rotVec.Z, 2) }
			};

			vector3df final = vector3df(
				tmp1.X * rotMatrix[0][0] + 
				tmp1.Y * rotMatrix[0][1] + 
				tmp1.Z * rotMatrix[0][2],
				tmp1.X * rotMatrix[1][0] + 
				tmp1.Y * rotMatrix[1][1] + 
				tmp1.Z * rotMatrix[1][2],
				tmp1.X * rotMatrix[2][0] + 
				tmp1.Y * rotMatrix[2][1] + 
				tmp1.Z * rotMatrix[2][2]
			);

			cam->setTarget(cam->getPosition() + final);
		}
		else
		{
			cam->setTarget(target);
			cout << "setTarget\n";
		}
		ReleaseMutex(mutex);
	}
	return NULL;
}


DWORD WINAPI Moving(void* arg)
{
	Sleep(1000);
	DWORD threadId;
	HANDLE thread1 = CreateThread(NULL, 0, Rotating, NULL, 0, &threadId);
	while(1)
	{
		WaitForSingleObject(mutex, INFINITE);
		cam->setPosition(cam->getPosition() + vector3df(0.1f, 0.2f, 0.1f));
		ReleaseMutex(mutex);
		Sleep(10);
	}
	doRotating = false;
	return NULL;
}

DWORD WINAPI Temp(void* arg)
{
	Sleep(7000);
	WaitForSingleObject(mutex, INFINITE);
	cam->setTarget(cam->getTarget() + vector3df(154.4f, 243.7f, 121.1f));
	ReleaseMutex(mutex);
	return NULL;
}