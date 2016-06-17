#pragma once
#include <Windows.h>
#include <d2d1.h>

const wchar_t RenderWindowClassName[] = L"RenderWindow";

class RenderWindow
{
private:
	HWND hWindow;
	UINT8 *bmp;
	ID2D1Factory *d2dFact;
	ID2D1HwndRenderTarget *d2dRTarget;
	ID2D1Bitmap* d2dBmp;
public:
	RenderWindow(HINSTANCE hInstance, int nCmdShow);
	~RenderWindow();

	void setPixel(const unsigned int x, const unsigned int y, const unsigned char r, const unsigned char g, const unsigned char b);

	static LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
};

