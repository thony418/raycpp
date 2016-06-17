#include <Windows.h>
#include "RenderWindow.h"

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR lpCmdLine, int nCmdShow) {
	RenderWindow mainWindow(hInstance, nCmdShow);
	MSG msg = {};

	mainWindow.setPixel(1, 0, 255, 0, 0);
	mainWindow.setPixel(2, 0, 255, 0, 0);
	mainWindow.setPixel(3, 0, 255, 0, 0);

	mainWindow.setPixel(4, 0, 0, 255, 0);
	mainWindow.setPixel(5, 0, 0, 255, 0);
	mainWindow.setPixel(6, 0, 0, 255, 0);

	mainWindow.setPixel(7, 0, 0, 0, 255);
	mainWindow.setPixel(8, 0, 0, 0, 255);
	mainWindow.setPixel(9, 0, 0, 0, 255);

	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return msg.wParam;
}