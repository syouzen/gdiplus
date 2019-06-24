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
		
		hdc = BeginPaint(hWnd, &ps);
		SetGraphicsMode(hdc, GM_ADVANCED);

		Gdiplus::GpStatus stat = Gdiplus::DllExports::GdipCreateFromHDC(hdc, &graphics);

		Gdiplus::GpPoint  point1(100, 100);
		Gdiplus::GpPoint  point2(200, 100);
		Gdiplus::GpPoint  point3(200, 200);
		Gdiplus::GpPoint  point4(100, 200);
		Gdiplus::GpPoint  point5(100, 100);
		Gdiplus::GpPoint  points[5] = { point1, point2, point3, point4, point5 };

		Gdiplus::GpPath* path = NULL;
		Gdiplus::GpPen* pen = NULL;
		BOOL result;

		Gdiplus::DllExports::GdipCreatePath(Gdiplus::FillModeAlternate, &path);
		Gdiplus::DllExports::GdipCreatePen1(0xFF000000, 10.0, Gdiplus::UnitPixel, &pen);

		Gdiplus::DllExports::GdipAddPathPolygonI(path, points, 5);

		Gdiplus::DllExports::GdipCreateMatrix2(1, 0, 0, 1, 1000, 1000, &mat);
		Gdiplus::DllExports::GdipSetWorldTransform(graphics, mat);
		Gdiplus::DllExports::GdipDeleteMatrix(mat);

		Gdiplus::DllExports::GdipIsVisiblePathPoint(path, 150, 150, graphics, &result);

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