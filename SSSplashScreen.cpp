#include <windows.h>
#include <commctrl.h>

RECT Rect;

WNDCLASS wcl;
HINSTANCE hInstance = GetModuleHandle(0);
MSG msg;
BITMAP Bitmap;
HDC hdc, hCDC;
HBITMAP hBitmap;
PAINTSTRUCT ps;
wchar_t *szWinName = L"SSSplashScreen";
HWND hMainWnd, hIrrWnd;
wchar_t* File = new wchar_t[256];

#pragma comment(lib, "comctl32.lib")

POINT GetPictureSize(HBITMAP hBitmap)
{
	BITMAP bm; 
	GetObject(hBitmap, sizeof(BITMAP),(LPVOID) &bm);
	POINT size;
	size.x = bm.bmWidth;
	size.y = bm.bmHeight;
	return size;
}

void DrawBitmap(HDC hdc, HBITMAP hBitmap, int xStart, int yStart) 
{ 
	BITMAP bm; 
	HDC hdcMem; 
	POINT ptSize, ptOrg; 

	hdcMem = CreateCompatibleDC(hdc); 

	SelectObject(hdcMem, hBitmap); 
	SetMapMode(hdcMem, GetMapMode(hdc)); 
	GetObject(hBitmap, sizeof(BITMAP),(LPVOID) &bm); 
	ptSize.x = bm.bmWidth; 
	ptSize.y = bm.bmHeight; 
	DPtoLP(hdc, &ptSize, 1); 
	ptOrg.x = 0; 
	ptOrg.y = 0; 
	DPtoLP(hdcMem, &ptOrg, 1); 
	BitBlt( 
		hdc, xStart, yStart, ptSize.x, ptSize.y, 
		hdcMem, ptOrg.x, ptOrg.y, SRCCOPY 
		); 
	DeleteDC(hdcMem); 
}

LRESULT CALLBACK WindowFunc(HWND, UINT, WPARAM, LPARAM);
void CrWind();

void ShowSplash(wchar_t* File)
{
	wcscpy_s(::File, 256, File);
	hIrrWnd = FindWindow(L"CIrrDeviceWin32", NULL);
	ShowWindow(hIrrWnd, SW_HIDE);
	DWORD threadId; // »дентификатор потока
	HANDLE thread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)CrWind, NULL, 0, &threadId);
}

void HideSplash()
{
	ShowWindow(hIrrWnd, SW_SHOW);
	ShowWindow(hMainWnd, SW_HIDE);
	DestroyWindow(hMainWnd);
}

void CrWind()
{
	InitCommonControls();
	wcl.hInstance = hInstance;
	wcl.lpszClassName = szWinName;
	wcl.lpfnWndProc = WindowFunc;
	wcl.style = CS_HREDRAW | CS_VREDRAW;
	wcl.hIcon = LoadIcon(NULL, IDI_WINLOGO);
	wcl.hCursor = LoadCursor(NULL,IDC_ARROW);
	wcl.lpszMenuName = NULL;
	wcl.cbClsExtra = 0;
	wcl.cbWndExtra = 0;
	wcl.hbrBackground = (HBRUSH)COLOR_WINDOW;

	//регестрируем оконный класс
	RegisterClass(&wcl);

	hBitmap = (HBITMAP)LoadImage(GetModuleHandle(0), File, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

	POINT PictureSize;
	PictureSize = GetPictureSize(hBitmap);

	//создаем главное окно и элементы управлени€
	hMainWnd = CreateWindowEx(WS_EX_TOPMOST, szWinName, L"ѕростое окно на API.", WS_POPUP|WS_VISIBLE, 1280 / 2 - PictureSize.x / 2, 1024 / 2 - PictureSize.y / 2,
		PictureSize.x, PictureSize.y, HWND_DESKTOP, NULL, hInstance, NULL);

	ShowWindow(hMainWnd, SW_SHOW);
	UpdateWindow(hMainWnd);

	GetClientRect(hMainWnd, &Rect);

	//цикл обработки сообщений
	while(GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}


LRESULT CALLBACK WindowFunc(HWND hMainWnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	switch(iMsg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_PAINT:
		{
			GetClientRect(hMainWnd, &Rect);
			hdc=BeginPaint(hMainWnd,&ps);
			DrawBitmap(hdc, hBitmap, 0, 0);
			DeleteObject(hBitmap);
			hCDC = NULL;
			EndPaint(hMainWnd,&ps);
			break;
		}

	default:
		return DefWindowProc(hMainWnd, iMsg, wParam, lParam);
	}

	return 0;
}