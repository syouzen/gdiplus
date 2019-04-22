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

		hdc = BeginPaint(hWnd, &ps);

		Gdiplus::GpStatus stat = Gdiplus::DllExports::GdipCreateFromHDC(hdc, &graphics);

		Gdiplus::GpBitmap* src_bitmap = NULL;
		Gdiplus::GpRect src_rect;

		src_rect.X = 0;
		src_rect.Y = 0;
		src_rect.Width = 100;
		src_rect.Height = 100;

		Gdiplus::DllExports::GdipCreateBitmapFromScan0(100, 100, 400, PixelFormat32bppPARGB, NULL, &src_bitmap);

		for (int h = 0; h < 100; h++)
		{
			for (int w = 0; w < 100; w++)
			{
				if (h >= 30 && h <= 70)
					Gdiplus::DllExports::GdipBitmapSetPixel(src_bitmap, w, h, 0xFFFFFF00);
				else
					Gdiplus::DllExports::GdipBitmapSetPixel(src_bitmap, w, h, 0xFFFF0000);
			}
		}

		HBITMAP hbitmap;
		HDC memdc;
		Gdiplus::DllExports::GdipCreateHBITMAPFromBitmap(src_bitmap, &hbitmap, 0);

		memdc = CreateCompatibleDC(hdc);

		SelectObject(memdc, hbitmap);
		StretchBlt(hdc, 0, 0, 100, 100, memdc, 0, 0, 100, 100, SRCCOPY);
		TransparentBlt(hdc, 150, 150, 100, 100, memdc, 0, 0, 100, 100, RGB(255, 0, 0));
		
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