#include <Windows.h>
#include "RenderWindow.h"
#include "Camera.h"
#include "Sphere.h"
#include "collision.h"
#include "Ray.h"

void renderingLoop(RenderWindow& window, Camera& cam, vector<SceneObject*> objVect) {
	
	for (int x = 0; x < 1024; x++) {
		for (int y = 0; y < 768; y++) {
			Ray currRay(cam.getRay(x, y));
			pair<Vec3, SceneObject*> intersection = collide(currRay, objVect);

			if (intersection.second != nullptr)
				window.setPixel(x, y, 255, 0, 0);
			else
				window.setPixel(x, y, 20, 20, 20);
		}
	}
}

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR lpCmdLine, int nCmdShow) {
	RenderWindow mainWindow(hInstance, nCmdShow);
	Camera cam(Vec3(), Vec3(0.0f, 0.0f, 2.0f), 1024, 768);
	vector<SceneObject*> objVect;
	objVect.push_back(new Sphere(Vec3(0.5, 0.0, 5.0), 0.5));
	objVect.push_back(new Sphere(Vec3(-1.0, 0.0, 7.0), 1.0));

		renderingLoop(mainWindow, cam, objVect);

	MSG msg = {};
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return msg.wParam;
}