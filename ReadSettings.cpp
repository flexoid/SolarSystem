#include "ReadSettings.h"

const TCHAR* IniFile = L"./settings.ini";

std::string GetTexturesQuality()
{
	std::string TexturesPath;
	switch(GetPrivateProfileInt(L"Settings", L"Textures", 0, IniFile))
	{
	case 1:
		{
			TexturesPath = "./data/Textures/Low/";
			break;
		}
	case 2:
		{
			TexturesPath = "./data/Textures/Medium/";
			break;
		}
	case 3:
		{
			TexturesPath = "./data/Textures/High/";
			break;
		}
	case 4:
		{
			TexturesPath = "./data/Textures/Best/";
			break;
		}
	default:
		{
			TexturesPath = "./data/Textures/Medium/";
			break;
		}
	}
	return TexturesPath;
}

int GetDirectXVersion()
{
	switch(GetPrivateProfileInt(L"Settings", L"DeviceType", 0, IniFile))
	{
	case 1:
		return 1;
	case 2:
		return 2;
	default:
		return 1;
	}
}

bool GetScreenMode()
{
	return (bool)GetPrivateProfileInt(L"Settings", L"Fullscreen", 0, IniFile);
}