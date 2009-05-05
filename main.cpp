#include <irrlicht.h>
#include <iostream>
#include "SSPlanets.h"
#include "SSEventReceiver.h"
#include "SSMoveCameraTo.h"

#pragma comment(lib, "Irrlicht.lib")

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

HANDLE mutex;
DWORD WINAPI renderWorker (void* arg);

IrrlichtDevice* device;
IVideoDriver* driver;
ISceneManager* smgr;
IGUIEnvironment* guienv;

//Параметры анимации
bool IsActiveMoving = true;
bool IsActiveRotating = true;
f32 koeffSpeed = 0.3f;

//Планеты
ISceneNode* sun;
ISceneNode* earth;
ISceneNode* pluto;
ISceneNode* mercury;
ISceneNode* venus;
ISceneNode* mars;
ISceneNode* jupiter;
ISceneNode* saturn;
ISceneNode* uranus;
ISceneNode* neptune;

ICameraSceneNode *camera; //Камера

void test(void)
{
	while(1)
	{
		u32 time;
		Sleep(3000);
		time = SSMoveCameraTo(camera, sun);
		Sleep(time + 2000);
		time = SSMoveCameraTo(camera, earth);
		Sleep(time + 2000);
		time = SSMoveCameraTo(camera, mercury);
		Sleep(time + 2000);
		time = SSMoveCameraTo(camera, pluto);
		Sleep(time + 2000);
		time = SSMoveCameraTo(camera, venus);
		Sleep(time + 2000);
		time = SSMoveCameraTo(camera, mars);
		Sleep(time + 2000);
		time = SSMoveCameraTo(camera, jupiter);
		Sleep(time + 2000);
		time = SSMoveCameraTo(camera, saturn);
		Sleep(time + 2000);
		time = SSMoveCameraTo(camera, uranus);
		Sleep(time + 2000);
		time = SSMoveCameraTo(camera, neptune);
		Sleep(time + 2000);
	}
}

int main()
{

	char i;
	video::E_DRIVER_TYPE driverType;

	printf("Please select the driver you want for this example:\n"\
		" (a) Direct3D 9.0c\n (b) Direct3D 8.1\n (c) OpenGL 1.5\n"\
		" (d) Software Renderer\n (e) Burning's Software Renderer\n"\
		" (f) NullDevice\n (otherKey) exit\n\n");

	std::cin >> i;

	switch(i)
	{
	case 'a': driverType = video::EDT_DIRECT3D9;break;
	case 'b': driverType = video::EDT_DIRECT3D8;break;
	case 'c': driverType = video::EDT_OPENGL;   break;
	case 'd': driverType = video::EDT_SOFTWARE; break;
	case 'e': driverType = video::EDT_BURNINGSVIDEO;break;
	case 'f': driverType = video::EDT_NULL;     break;
	default: return 1;
	}

	device = createDevice(driverType, dimension2d<s32>(1024, 768),
		32, false, false, false, 0);
	device->setWindowCaption(L"SunSyst   by FlexoID & Evilguc");

	driver = device->getVideoDriver();
	smgr = device->getSceneManager();
	guienv = device->getGUIEnvironment();

	SSEventReceiver receiver;
	device->setEventReceiver(&receiver);

	//-------------Создание планет
	sun = AddSun();
	earth = AddEarth();
	pluto = AddPluto();
	mercury = AddMercury();
	venus = AddVenus();
	mars = AddMars();
	jupiter = AddJupiter();
	saturn = AddSaturn();
	uranus = AddUranus();
	neptune = AddNeptune();
	//--------
	
	//----Небо
	ITexture *skyTexture = driver->getTexture(".\\data\\hipp8.jpg");
	smgr->addSkyBoxSceneNode(skyTexture, skyTexture, skyTexture, 
		skyTexture, skyTexture, skyTexture);
	//--------

	camera = smgr->addCameraSceneNode(0, vector3df(-700.0f, 500.0f, -700.0f));
	//camera = smgr->addCameraSceneNodeFPS();
	camera->setFarValue(999999.0f);

	//-----Реализация рендеринга в отдельном потоке-----------
	mutex = CreateMutex (NULL, FALSE, NULL);

	DWORD threadId; // Идентификатор потока
	HANDLE thread = CreateThread(NULL, 0, renderWorker, NULL, 0, &threadId);

	DWORD threadId1;
	HANDLE thread1 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)test, NULL, 0, &threadId1);

	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}

DWORD WINAPI renderWorker (void* arg)
{
	u32 frames = 0;
	IVideoDriver* driver = device->getVideoDriver();
	while(device->run())
	{
		WaitForSingleObject(mutex, INFINITE);

		driver->beginScene(true, true, video::SColor(0, 0, 0, 0));
		smgr->drawAll();
		guienv->drawAll();
		MovingCamera(); // Перемещение камеры
		driver->endScene();

		if (++frames==100)
		{
			core::stringw str = L"Irrlicht Engine [";
			str += driver->getName();
			str += L"] FPS: ";
			str += (s32)driver->getFPS();

			device->setWindowCaption(str.c_str());
			frames=0;
		}
		ReleaseMutex(mutex);

		device->yield();
	}
	return NULL;
}