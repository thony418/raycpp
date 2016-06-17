#include "RenderWindow.h"

RenderWindow *winInstance = NULL;

LRESULT CALLBACK RenderWindow::WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	switch (uMsg) {
	case WM_PAINT:
		winInstance->d2dBmp->CopyFromMemory(NULL, winInstance->bmp, 1024 * 4);
		winInstance->d2dRTarget->BeginDraw();
		winInstance->d2dRTarget->DrawBitmap(winInstance->d2dBmp);
		winInstance->d2dRTarget->EndDraw();
		break;
	case WM_CLOSE:
		DestroyWindow(hWnd);
		break;
	case WM_DESTROY:
		winInstance->d2dRTarget->Release();
		winInstance->d2dFact->Release();
		winInstance->d2dBmp->Release();
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}
	return 0;
}

RenderWindow::RenderWindow(HINSTANCE hInstance, int nCmdShow)
{
	if (winInstance == NULL)
		winInstance = this;
	else
		abort();

	// On crée un buffer d'image
	this->bmp = (UINT8*)malloc(1028 * 768 * 4);

	// On nettoie le buffer d'image
	for (int i = 0; i < 1024 * 768; i++) {
		bmp[i * 4] = 0;
		bmp[i * 4 + 1] = 0;
		bmp[i * 4 + 2] = 0;
		bmp[i * 4 + 3] = 0;
	}

	HRESULT hr;

	hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &d2dFact);
	if (hr != S_OK) abort();

	WNDCLASSEX wc = { };
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = 0;
	wc.lpfnWndProc = RenderWindow::WndProc;
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

	hWindow = CreateWindowEx(
		0,
		RenderWindowClassName,
		L"RayCPP",
		WS_OVERLAPPEDWINDOW ^ (WS_MAXIMIZEBOX | WS_THICKFRAME),
		CW_USEDEFAULT, CW_USEDEFAULT,
		winRect.right - winRect.left, winRect.bottom - winRect.top,
		NULL, NULL, hInstance, NULL);
	

	hr = d2dFact->CreateHwndRenderTarget(
		D2D1::RenderTargetProperties(),
		D2D1::HwndRenderTargetProperties(
			hWindow,
			D2D1::SizeU(
				winRect.right - winRect.left,
				winRect.bottom - winRect.top
			)
		),
		&d2dRTarget
	);
	if (hr != S_OK) abort();

	hr = d2dRTarget->CreateBitmap(
		D2D1::SizeU(1024, 768),
		D2D1::BitmapProperties(D2D1::PixelFormat(DXGI_FORMAT_B8G8R8A8_UNORM, D2D1_ALPHA_MODE_IGNORE)),
		&d2dBmp);
	if (hr != S_OK) abort();

	ShowWindow(hWindow, nCmdShow);
}

void RenderWindow::setPixel(const unsigned int x, const unsigned int y, const unsigned char r, const unsigned char g, const unsigned char b) {
	bmp[y * 1024 * 4 + x * 4 + 0] = b;
	bmp[y * 1024 * 4 + x * 4 + 1] = g;
	bmp[y * 1024 * 4 + x * 4 + 2] = r;
	//bmp[y * 1024 * 4 + x * 4 + 3] // alpha channel not used
}

RenderWindow::~RenderWindow()
{
	free(bmp);
}
