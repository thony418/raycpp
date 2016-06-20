#include <Windows.h>
#include "RenderWindow.h"
#include "Camera.h"
#include "Scene.h"
#include "Sphere.h"
#include "Ray.h"
#include "Color.h"

void renderingLoop(RenderWindow& window, Camera& cam, Sphere& sp) {
	Color tmp_color;
	for (int x = 0; x < 1024; x++) {
		for (int y = 0; y < 768; y++) {
			Ray currRay(cam.getRay(x, y));

			pair<bool, Vec3> intersection = sp.intersect(currRay);

			if (intersection.first) {
				tmp_color = currRay.phong_shading(intersection.second, Vec3(1.0,1.0,1.0), Material(0.2f, 0.5f, 0.5f, Color(255, 0, 0)),
					Light());
				int r = (int)(tmp_color.getX() * 255);
				int g = (int)(tmp_color.getY() * 255);
				int b = (int)(tmp_color.getZ() * 255);
				window.setPixel(x, y, r, g, b);
			} else {
				window.setPixel(x, y, 20, 20, 20);
			}
		}
	}
}

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR lpCmdLine, int nCmdShow) {
	RenderWindow mainWindow(hInstance, nCmdShow);
	Camera cam(Vec3(), Vec3(0.0f, 0.0f, 2.0f), 1024, 768);
	Sphere sp(Vec3(0.5f, 0.0f, 5.0f), 0.5f);

	renderingLoop(mainWindow, cam, sp);


	MSG msg = {};
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return msg.wParam;
}