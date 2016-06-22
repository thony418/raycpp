/**
* \author Marie DARRIGOL & Anthony LEONARD & Ophélie PELLOUX-PRAYER & Olivier SOLDANO
* \project Ray-Tracing
* \file RenderWindow.h
* \brief Window in which the picture is rendered
*/

#pragma once
#include <Windows.h>
#include <d2d1.h>

const wchar_t RenderWindowClassName[] = L"RenderWindow";

class RenderWindow
{
private:
	HWND hWindow; // window handler
	UINT8 *bmp; // Rendering buffer

	// Some handler for Direct2D
	ID2D1Factory *d2dFact;
	ID2D1HwndRenderTarget *d2dRTarget;
	ID2D1Bitmap* d2dBmp;
public:
	RenderWindow(HINSTANCE hInstance, int nCmdShow);
	~RenderWindow();

	// Set a particular pixel with a specified color
	void setPixel(const unsigned int x, const unsigned int y, const unsigned char r, const unsigned char g, const unsigned char b);

	static LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
};

