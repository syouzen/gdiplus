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
		Gdiplus::GpGraphics* graphics = NULL;
		Gdiplus::GpGraphics* graphics2 = NULL;
		Gdiplus::GpGraphics* graphics3 = NULL;

		hdc = BeginPaint(hWnd, &ps);

		Gdiplus::GpStatus stat = Gdiplus::DllExports::GdipCreateFromHDC(hdc, &graphics);

		Gdiplus::GpBitmap* src_bitmap = NULL;
		Gdiplus::GpBitmap* dst_bitmap = NULL;
		Gdiplus::GpBitmap* dst_bitmap2 = NULL;
		Gdiplus::GpRect src_rect;
		Gdiplus::BitmapData src_data;

		src_rect.X = 0;
		src_rect.Y = 0;
		src_rect.Width = 100;
		src_rect.Height = 100;
				
		Gdiplus::DllExports::GdipCreateBitmapFromScan0(100, 100, 400, PixelFormat32bppPARGB, NULL, &src_bitmap);
		Gdiplus::DllExports::GdipCreateBitmapFromScan0(100, 100, 400, PixelFormat32bppPARGB, NULL, &dst_bitmap);
		Gdiplus::DllExports::GdipCreateBitmapFromScan0(100, 100, 400, PixelFormat32bppPARGB, NULL, &dst_bitmap2);
		Gdiplus::DllExports::GdipGetImageGraphicsContext(dst_bitmap, &graphics2);
		Gdiplus::DllExports::GdipGetImageGraphicsContext(dst_bitmap2, &graphics3);
				
		Gdiplus::DllExports::GdipBitmapLockBits(src_bitmap, &src_rect, Gdiplus::ImageLockModeRead | Gdiplus::ImageLockModeWrite, PixelFormat32bppARGB, &src_data);

		for (int h = 0; h < 100; h++) {
			BYTE *src = (BYTE*)src_data.Scan0 + h * 400;
			for (int w = 0; w < 100; w++) {
				*src++ = 0x8A;
				*src++ = 0x5D;
				*src++ = 0x38;
				*src++ = 0x7E;
			}
		}
		
		Gdiplus::DllExports::GdipBitmapUnlockBits(src_bitmap, &src_data);

		Gdiplus::DllExports::GdipDrawImageRectRectI(graphics2, src_bitmap, 0, 0, 100, 100, 0, 0, 100, 100, Gdiplus::UnitPixel, NULL, NULL, NULL);
		Gdiplus::DllExports::GdipDrawImageRectRectI(graphics3, dst_bitmap, 0, 0, 100, 100, 0, 0, 100, 100, Gdiplus::UnitPixel, NULL, NULL, NULL);
		Gdiplus::DllExports::GdipDrawImageRectRectI(graphics, dst_bitmap2, 0, 0, 100, 100, 0, 0, 100, 100, Gdiplus::UnitPixel, NULL, NULL, NULL);

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