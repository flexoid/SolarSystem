#include <irrlicht.h>
#include <windows.h>
#include <iostream>
#include "ISceneNodeAnimatorFlyEllipce.h"
#include "EventDispatcher.h"

#pragma comment(lib, "Irrlicht.lib")

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

IrrlichtDevice* device;
ISceneManager* smgr;
HANDLE mutex;
DWORD WINAPI renderWorker (void* arg);
bool eventHandler (const SEvent& irrEvent);

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

	IVideoDriver* driver = device->getVideoDriver();
	smgr = device->getSceneManager();
	IGUIEnvironment* guienv = device->getGUIEnvironment();
	
	smgr->addCameraSceneNode(NULL, vector3df(0, 0, -20), vector3df(0, 0, 0));

	//-----Реализация рендеринга в отдельном потоке-----------
	EventDispatcher dispatcher;
	dispatcher.eventHandler = eventHandler;
	mutex = CreateMutex (NULL, FALSE, NULL);
	device->setEventReceiver(&dispatcher);

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

bool eventHandler (const SEvent& irrEvent)
{
	// Переводим объект синхронизации в состяние "занято".
	// Теперь другой поток, вызвав WaitForSingleObject(mutex, INFINITE), будет
	// ждать, пока объект синхронизации не перейдёт в состояние "свободно"
	WaitForSingleObject(mutex, INFINITE);
	
	// Обращаемся к общим данным здесь. Например к ISceneManager
	smgr->getActiveCamera()->OnEvent(irrEvent);
	
	// Переводим объект синхронизации в состяние "свободно".
	// Теперь нельзя обращаться к общим данным
	ReleaseMutex(mutex);
	return true;
}