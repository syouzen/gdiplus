#include <windows.h>

#define GDIPVER 0x0110
#include <gdiplus.h>
#include <stdio.h>

#pragma comment (lib,"Gdiplus.lib")

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
		Gdiplus::GpGraphics* graphics;

		hdc = BeginPaint(hWnd, &ps);

		// Rectangle 1					

		Gdiplus::GpStatus stat = Gdiplus::DllExports::GdipCreateFromHDC(hdc, &graphics);

		Gdiplus::DllExports::GdipSetPageUnit(graphics, Gdiplus::UnitPixel);
		Gdiplus::DllExports::GdipSetCompositingMode(graphics, Gdiplus::CompositingModeSourceOver);
		Gdiplus::DllExports::GdipSetSmoothingMode(graphics, Gdiplus::SmoothingModeAntiAlias8x4);

		Gdiplus::GpPoint  point1(100, 100);
		Gdiplus::GpPoint  point2(800, 100);
		Gdiplus::GpPoint  point3(800, 200);
		Gdiplus::GpPoint  point4(100, 200);
		Gdiplus::GpPoint  point5(100, 100);
		Gdiplus::GpPoint  points[5] = { point1, point2, point3, point4, point5 };

		Gdiplus::GpPath* path = NULL;
		Gdiplus::GpRegion* region = NULL;
		Gdiplus::GpSolidFill* pBrush;

		Gdiplus::DllExports::GdipCreatePath(Gdiplus::FillModeAlternate, &path);
		Gdiplus::DllExports::GdipAddPathPolygonI(path, points, 5);
		Gdiplus::DllExports::GdipCreateRegionPath(path, &region);
		Gdiplus::DllExports::GdipSetClipRegion(graphics, region, Gdiplus::CombineModeReplace);
		Gdiplus::DllExports::GdipCreateSolidFill(Gdiplus::ARGB(4278190080), &pBrush);
		Gdiplus::DllExports::GdipFillPolygonI(graphics, pBrush, points, 5, Gdiplus::FillModeAlternate);

		Gdiplus::DllExports::GdipDeleteBrush(pBrush);
		Gdiplus::DllExports::GdipResetClip(graphics);
		Gdiplus::DllExports::GdipDeleteRegion(region);
		Gdiplus::DllExports::GdipDeletePath(path);
		Gdiplus::DllExports::GdipDeleteGraphics(graphics);

		// Rectangle 2 

		Gdiplus::GpStatus stat2 = Gdiplus::DllExports::GdipCreateFromHDC(hdc, &graphics);

		Gdiplus::DllExports::GdipSetPageUnit(graphics, Gdiplus::UnitPixel);
		Gdiplus::DllExports::GdipSetCompositingMode(graphics, Gdiplus::CompositingModeSourceOver);
		Gdiplus::DllExports::GdipSetSmoothingMode(graphics, Gdiplus::SmoothingModeAntiAlias8x4);

		Gdiplus::GpPoint  spoint1(100, 200);
		Gdiplus::GpPoint  spoint2(800, 200);
		Gdiplus::GpPoint  spoint3(800, 300);
		Gdiplus::GpPoint  spoint4(100, 300);
		Gdiplus::GpPoint  spoint5(100, 200);
		Gdiplus::GpPoint  spoints[5] = { spoint1, spoint2, spoint3, spoint4, spoint5 };

		Gdiplus::GpPath* spath = NULL;
		Gdiplus::GpRegion* sregion = NULL;
		Gdiplus::GpSolidFill* spBrush;

		Gdiplus::DllExports::GdipCreatePath(Gdiplus::FillModeAlternate, &spath);
		Gdiplus::DllExports::GdipAddPathPolygonI(spath, spoints, 5);
		Gdiplus::DllExports::GdipCreateRegionPath(spath, &sregion);
		Gdiplus::DllExports::GdipSetClipRegion(graphics, sregion, Gdiplus::CombineModeReplace);
		Gdiplus::DllExports::GdipCreateSolidFill(Gdiplus::ARGB(4278190080), &spBrush);
		Gdiplus::DllExports::GdipFillPolygonI(graphics, spBrush, spoints, 5, Gdiplus::FillModeAlternate);

		Gdiplus::DllExports::GdipDeleteBrush(spBrush);
		Gdiplus::DllExports::GdipResetClip(graphics);
		Gdiplus::DllExports::GdipDeleteRegion(sregion);
		Gdiplus::DllExports::GdipDeletePath(spath);
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