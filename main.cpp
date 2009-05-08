#include <irrlicht.h>
#include <iostream>
#include "SSPlanets.h"
#include "SSEventReceiver.h"
#include "SSMoveCameraTo.h"

#include "SSGUI.h"

#include "SSSplashScreen.h"
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
f32 koeffSpeed = 0.15f;
f32 koeffOfDist = 4.0f;


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

ISceneNode* Planets[10];

ICameraSceneNode *camera; //Камера

void GlobalView()
{
	SSCameraStartPos(camera);
}

void PrevPlanet()
{
	currentPlanetID--;
	if (currentPlanetID < 0)
		currentPlanetID = 9;
	SSMoveCameraTo(camera, Planets[currentPlanetID]);
}

void NextPlanet()
{
	currentPlanetID++;
	if (currentPlanetID > 9)
		currentPlanetID = 0;
	SSMoveCameraTo(camera, Planets[currentPlanetID]);
}

void Minimize()
{
	HWND hWnd = FindWindow(L"CIrrDeviceWin32", 0);
	ShowWindow(hWnd, SW_MINIMIZE);
}

void Exit()
{
	device->closeDevice();
}

void SideNavigateBarCallback(s32 groupID, s32 buttonID)
{
	if (groupID == 0 && buttonID == 0)
	{
		currentPlanetID = 0;
		SSMoveCameraTo(camera, sun);
	}
	if (groupID == 1 && buttonID == 0)
	{
		currentPlanetID = 1;
		SSMoveCameraTo(camera, mercury);
	}
	if (groupID == 1 && buttonID == 1)
	{
		currentPlanetID = 2;
		SSMoveCameraTo(camera, venus);
	}
	if (groupID == 1 && buttonID == 2)
	{
		currentPlanetID = 3;
		SSMoveCameraTo(camera, earth);
	}
	if (groupID == 1 && buttonID == 3)
	{
		currentPlanetID = 4;
		SSMoveCameraTo(camera, mars);
	}
	if (groupID == 1 && buttonID == 4)
	{
		currentPlanetID = 5;
		SSMoveCameraTo(camera, jupiter);
	}
	if (groupID == 1 && buttonID == 5)
	{
		currentPlanetID = 6;
		SSMoveCameraTo(camera, saturn);
	}
	if (groupID == 1 && buttonID == 6)
	{
		currentPlanetID = 7;
		SSMoveCameraTo(camera, uranus);
	}
	if (groupID == 1 && buttonID == 7)
	{
		currentPlanetID = 8;
		SSMoveCameraTo(camera, neptune);
	}

	if (groupID == 2 && buttonID == 0)
	{
		currentPlanetID = 9;
		SSMoveCameraTo(camera, pluto);
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

	ShowSplash(L"./data/Images/SplashScreen/SplashScreen.bmp");

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
	Planets[0] = sun;
	Planets[1] = mercury;
	Planets[2] = venus;
	Planets[3] = earth;
	Planets[4] = mars;
	Planets[5] = jupiter;
	Planets[6] = saturn;
	Planets[7] = uranus;
	Planets[8] = neptune;
	Planets[9] = pluto;
	//--------

	//----Небо
	ITexture *skyTexture = driver->getTexture("./data/Textures/Hi/Sky/Sky.jpg");
	smgr->addSkyBoxSceneNode(skyTexture, skyTexture, skyTexture, 
		skyTexture, skyTexture, skyTexture);
	//--------

	camera = smgr->addCameraSceneNode(0, vector3df(-700.0f, 500.0f, -700.0f));
	//camera = smgr->addCameraSceneNodeFPS();
	camera->setFarValue(999999.0f);

	InitializeGUI(guienv);

	//-----Реализация рендеринга в отдельном потоке-----------
	mutex = CreateMutex (NULL, FALSE, NULL);

	DWORD threadId; // Идентификатор потока
	HANDLE thread = CreateThread(NULL, 0, renderWorker, NULL, 0, &threadId);

	koeffOfDist = (f32)(DistanceScrollBar->getPos() / 1000.0f + 1.4f);

	HideSplash();

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