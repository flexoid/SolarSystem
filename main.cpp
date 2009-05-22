#include <irrlicht.h>
#include <iostream>
#include "SSPlanets.h"
#include "SSEventReceiver.h"
#include "SSMoveCameraTo.h"
#include "SSReadSettings.h"
#include "SSFreeFlightCameraMode.h"
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
f32 koeffSpeed = 0.05f;
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

ICameraSceneNode *camera; //Камера

std::string TexturesPath;

SSFreeFlightCameraMode *FreeFlightMode;
SSGUIStatusBar *StatusBar;

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

void FreeFlight()
{
	FreeFlightMode->On();
}

void About()
{
	AboutWindow->show("./data/GUI/Source/AboutWindow/Image/image.png");
}

void Minimize()
{
	HWND hWnd = FindWindow(L"CIrrDeviceWin32", 0);
	ShowWindow(hWnd, SW_MINIMIZE);
}

void Exit()
{
	WritePrivateProfileString(L"Flags", L"Crashed", L"0", L"./settings.ini");
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

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	TexturesPath = GetTexturesQuality();

	bool fullscreen = GetScreenMode();

	char i;
	video::E_DRIVER_TYPE driverType;

	i = GetDirectXVersion();

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
		32, fullscreen, false, false, 0);
	device->setWindowCaption(L"Солнечная система");

	HWND Handle = FindWindow(L"CIrrDeviceWin32", NULL);
	DeleteMenu(GetSystemMenu(Handle, 0), SC_CLOSE, MF_BYCOMMAND);
	CloseHandle(Handle);

	if (!fullscreen)
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
	//--------

	//----Небо
	ITexture *skyTexture = driver->getTexture(std::string(TexturesPath + "Sky/Sky.jpg").c_str());
	smgr->addSkyBoxSceneNode(skyTexture, skyTexture, skyTexture, 
		skyTexture, skyTexture, skyTexture);
	//--------

	camera = smgr->addCameraSceneNode(0, vector3df(-700.0f, 500.0f, -700.0f));
	//camera = smgr->addCameraSceneNodeFPS();
	camera->setFarValue(999999.0f);

	InitializeGUI(guienv);

	StatusBar = new SSGUIStatusBar(guienv, device->getCursorControl());
	StatusBar->setBackground(driver->getTexture("./data/GUI/Source/StatusBar/Background/background.png"));
	StatusBar->setIndention(2, 2);
	StatusBar->setTextAttributes(guienv->getFont("./data/GUI/Fonts/ArialNarrow(8px).xml"), SColor(255,255,255,255), 8);
	StatusBar->addElement(ZoomScrollBar);
	StatusBar->addElement(DistanceScrollBar);
	StatusBar->addElement(SpeedScrollBar);
	StatusBar->addElement(GlobalViewButton);
	StatusBar->addElement(PrevPlanetButton);
	StatusBar->addElement(NextPlanetButton);
	StatusBar->addElement(FreeFlightButton);
	//StatusBar->addElement(HelpButton);
	StatusBar->addElement(AboutButton);
	//StatusBar->addElement(MinimizeButton);
	StatusBar->addElement(ExitButton);
	StatusBar->addElement(SatelliteInfoWindow);
	GUIElements.push_back(StatusBar);

	FreeFlightMode = new SSFreeFlightCameraMode(guienv, smgr, device->getCursorControl(), GUIElements);
	FreeFlightMode->addCameraSceneNodeAnimators(Planets);
	FreeFlightMode->setLabel(L"Для выхода из режима свободного полета нажмите клавишу <пробел>", guienv->getFont("./data/GUI/Fonts/Calibri(14px)b.xml"));

	//-----Реализация рендеринга в отдельном потоке-----------
	mutex = CreateMutex (NULL, FALSE, NULL);

	DWORD threadId; // Идентификатор потока
	HANDLE thread = CreateThread(NULL, 0, renderWorker, NULL, 0, &threadId);

	koeffOfDist = (f32)(DistanceScrollBar->getPos() / 1000.0f + 1.4f);

	if (!fullscreen)
		HideSplash();

	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return 0;
}

DWORD WINAPI renderWorker (void* arg)
{
	//u32 frames = 0;
	IVideoDriver* driver = device->getVideoDriver();
	while(device->run())
	{
		WaitForSingleObject(mutex, INFINITE);

		driver->beginScene(true, true, video::SColor(0, 0, 0, 0));
		smgr->drawAll();
		guienv->drawAll();
		MovingCamera(); // Перемещение камеры
		driver->endScene();

		/*if (++frames==100)
		{
			core::stringw str = L"Irrlicht Engine [";
			str += driver->getName();
			str += L"] FPS: ";
			str += (s32)driver->getFPS();

			device->setWindowCaption(str.c_str());
			frames=0;
		}
		*/
		ReleaseMutex(mutex);

		device->yield();
	}
	return NULL;
}