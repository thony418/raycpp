#include "RenderWindow.h"

LRESULT CALLBACK RWWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	switch (uMsg) {
	case WM_CLOSE:
		DestroyWindow(hWnd);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}
	return 0;
}

RenderWindow::RenderWindow(HINSTANCE hInstance, int nCmdShow)
{
	WNDCLASSEX wc = { };
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = 0;
	wc.lpfnWndProc = RWWndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH) COLOR_WINDOW + 1;
	wc.lpszMenuName = NULL;
	wc.lpszClassName = RenderWindowClassName;
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	if (RegisterClassEx(&wc) == 0)
		abort();

	RECT winRect = RECT();
	winRect.top = 0;
	winRect.bottom = 768;
	winRect.left = 0;
	winRect.right = 1024;

	AdjustWindowRectEx(&winRect, WS_OVERLAPPEDWINDOW ^ WS_MAXIMIZEBOX, false, 0);

	hWindow = CreateWindowEx(
		0,
		RenderWindowClassName,
		L"RayCPP",
		WS_OVERLAPPEDWINDOW ^ WS_MAXIMIZEBOX,
		CW_USEDEFAULT, CW_USEDEFAULT,
		winRect.right - winRect.left, winRect.bottom - winRect.top,
		NULL, NULL, hInstance, NULL);

	ShowWindow(hWindow, nCmdShow);
}


RenderWindow::~RenderWindow()
{
}
