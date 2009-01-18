#include <irrlicht.h>
#include <windows.h>
#include <iostream>
#include "SSPlanets.h"
#include "SSEventReceiver.h"

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
bool IsActive = true;
f32 speed = 100.0f;

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

	device = createDevice(driverType, dimension2d<s32>(640, 480),
		32, false, false, false, 0);
	device->setWindowCaption(L"SunSyst   by FlexoID & Evilguc");

	driver = device->getVideoDriver();
	smgr = device->getSceneManager();
	guienv = device->getGUIEnvironment();

	SSEventReceiver receiver;
	device->setEventReceiver(&receiver);

	//-------------Создание планет
	ISceneNode* earth = AddEarth(driver, smgr);
	//--------

	smgr->addCameraSceneNode(NULL, vector3df(0, 0, -50), vector3df(0, 0, 0));

	//-----Реализация рендеринга в отдельном потоке-----------
	mutex = CreateMutex (NULL, FALSE, NULL);

	DWORD threadId; // Идентификатор потока
	HANDLE thread = CreateThread(NULL, 0, renderWorker, NULL, 0, &threadId);

	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}


DWORD WINAPI renderWorker (void* arg)
{
	IVideoDriver* driver = device->getVideoDriver();
	while(device->run())
	{  
		// Переводим объект синхронизации в состояние "занято".
		// Теперь другой поток, вызвав WaitForSingleObject(mutex, INFINITE), будет
		// ждать, пока объект синхронизации не перейдёт в состояние "свободно"
		WaitForSingleObject(mutex, INFINITE);

		// Обращаемся к общим данным здесь. Например к ISceneManager и IVideoDriver
		driver->beginScene(true, true, video::SColor(0, 0, 0, 0));
		smgr->drawAll();
		guienv->drawAll();
		driver->endScene();

		// Переводим объект синхронизации в состояние "свободно".
		// Теперь нельзя обращаться к общим данным
		ReleaseMutex(mutex);

		// Остонавить работу рендера, что бы уменьшить использование
		// времени текущим потоком
		device->yield();
	}
	return NULL;
}