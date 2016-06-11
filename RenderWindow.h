#pragma once
#include <Windows.h>

const wchar_t RenderWindowClassName[] = L"RenderWindow";

class RenderWindow
{
private:
	HWND hWindow;
public:
	RenderWindow(HINSTANCE hInstance, int nCmdShow);
	~RenderWindow();
};

