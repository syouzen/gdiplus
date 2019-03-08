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
		500,            // initial x size
		800,            // initial y size
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

		Gdiplus::GpStatus stat = Gdiplus::DllExports::GdipCreateFromHDC(hdc, &graphics);

		// Begin example. 
		Gdiplus::GpPointF pts[] = { 
			Gdiplus::GpPointF(100.0f,50.0f),
			Gdiplus::GpPointF(200.0f,70.0f),
			Gdiplus::GpPointF(300.0f,10.0f),
			Gdiplus::GpPointF(400.0f,50.0f)
		};

		Gdiplus::GpPath* path = nullptr;
		Gdiplus::GpPath* path2 = nullptr;

		Gdiplus::DllExports::GdipCreatePath(Gdiplus::FillModeAlternate, &path);

		Gdiplus::DllExports::GdipAddPathCurve(path, pts, 4);
		//Gdiplus::DllExports::GdipAddPathEllipse(path, 20.0f, 100.0f, 150.0f, 80.0f);
		//Gdiplus::DllExports::GdipAddPathBezier(path, 20.0f, 200.0f, 20.0f, 250.0f, 50.0f, 210.0f, 100.0f, 260.0f);

		// Path1 : Defalut Flatness
		Gdiplus::GpPen* pen = nullptr;
		Gdiplus::DllExports::GdipCreatePen1(Gdiplus::ARGB(4278190080), 5.0f, Gdiplus::UnitWorld, &pen);
		Gdiplus::DllExports::GdipDrawPath(graphics, pen, path);
		
		// Path2 : Apply Flatness
		for (int i = 0; i < 6; ++i) {
			Gdiplus::GpPath* path2 = nullptr;

			Gdiplus::GpPointF pts2[] = {
				Gdiplus::GpPointF(100.0f,150.0f + i*100.0f),
				Gdiplus::GpPointF(200.0f,170.0f + i*100.0f),
				Gdiplus::GpPointF(300.0f,110.0f + i*100.0f),
				Gdiplus::GpPointF(400.0f,150.0f + i*100.0f)
			};

			Gdiplus::DllExports::GdipCreatePath(Gdiplus::FillModeAlternate, &path2);
			Gdiplus::DllExports::GdipAddPathCurve(path2, pts2, 4);
			Gdiplus::DllExports::GdipFlattenPath(path2, NULL, 2 * ((float)i + 1.0f));
			Gdiplus::DllExports::GdipDrawPath(graphics, pen, path2);
			
			Gdiplus::DllExports::GdipDeletePath(path2);
		}
		
		Gdiplus::DllExports::GdipDeletePen(pen);
		Gdiplus::DllExports::GdipDeletePath(path);
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