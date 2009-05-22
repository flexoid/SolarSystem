#include "SSReadSettings.h"

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

char GetDirectXVersion()
{
	switch(GetPrivateProfileInt(L"Settings", L"DeviceType", 0, IniFile))
	{
	case 1:
		return 'a';
	case 2:
		return 'b';
	default:
		return 'a';
	}
}

bool GetScreenMode()
{
	if (GetPrivateProfileInt(L"Settings", L"Fullscreen", 0, IniFile))
		return true;
	else 
		return false;
}