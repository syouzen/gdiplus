#include <windows.h>

#define GDIPVER 0x0110
#include <gdiplus.h>
#include <stdio.h>

#pragma comment (lib,"Gdiplus.lib")
#pragma comment (lib, "Msimg32.lib")

HINSTANCE hInst = nullptr;
HDC memDC;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, PSTR, INT iCmdShow)
{
	HWND                hWnd;
	MSG                 msg;
	WNDCLASS            wndClass;
	Gdiplus::GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR           gdiplusToken;

	// Initialize GDI+.
	hInst = hInstance;
	Gdiplus::GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

	wndClass.style = CS_HREDRAW | CS_VREDRAW;
	wndClass.lpfnWndProc = WndProc;
	wndClass.cbClsExtra = 0;
	wndClass.cbWndExtra = 0;
	wndClass.hInstance = hInstance;
	wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndClass.lpszMenuName = NULL;
	wndClass.lpszClassName = TEXT("GettingStarted");

	RegisterClass(&wndClass);

	hWnd = CreateWindow(
		TEXT("GettingStarted"),   // window class name
		TEXT("Getting Started"),  // window caption
		WS_OVERLAPPEDWINDOW,      // window style
		CW_USEDEFAULT,            // initial x position
		CW_USEDEFAULT,            // initial y position
		900,            // initial x size
		450,            // initial y size
		NULL,                     // parent window handle
		NULL,                     // window menu handle
		hInstance,                // program instance handle
		NULL);                    // creation parameters

	ShowWindow(hWnd, iCmdShow);
	UpdateWindow(hWnd);

	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	Gdiplus::GdiplusShutdown(gdiplusToken);
	return msg.wParam;
}  // WinMain

LRESULT CALLBACK WndProc(HWND hWnd, UINT message,
						 WPARAM wParam, LPARAM lParam)
{
	HDC          hdc;
	PAINTSTRUCT  ps;

	switch (message)
	{
	case WM_PAINT:
	{
		Gdiplus::GpGraphics* graphics = NULL;
		Gdiplus::GpMatrix* mat = NULL;
		Gdiplus::GpRect rect;
		
		hdc = BeginPaint(hWnd, &ps);

		Gdiplus::GpStatus stat = Gdiplus::DllExports::GdipCreateFromHDC(hdc, &graphics);

		Gdiplus::DllExports::GdipSetClipRectI(graphics, 0, 0, 300, 300, Gdiplus::CombineModeReplace);

		Gdiplus::DllExports::GdipCreateMatrix2(1, 0, 0, 1, 0, -200, &mat);
		Gdiplus::DllExports::GdipSetWorldTransform(graphics, mat);
		Gdiplus::DllExports::GdipDeleteMatrix(mat);

		Gdiplus::DllExports::GdipGetClipBoundsI(graphics, &rect);


		Gdiplus::DllExports::GdipDeleteGraphics(graphics);

		EndPaint(hWnd, &ps);

		return 0;
	}
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
} // WndProc