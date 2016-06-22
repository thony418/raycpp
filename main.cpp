#include <Windows.h>
#include "RenderWindow.h"
#include "Camera.h"
#include "Sphere.h"
#include "Planar.h"
#include "collision.h"
#include "Ray.h"
#include <thread>
#include "Color.h"
#include "Octree.h"
#include <omp.h>
#include "Box.h"

void renderingLoop(RenderWindow* window, Camera* cam, Scene & scene) {
	Color tmp_color;
	Octree octree = Octree(scene.getSceneObjects());
	#pragma omp parallel for private(tmp_color)
	for (int x = 0; x < 1024; x++) {
		for (int y = 0; y < 768; y++) {
			Ray currRay(cam->getRay(x, y));
			tmp_color = currRay.phong_shading(scene, octree);
			int r = (int)(tmp_color.getX() * 255);
			int g = (int)(tmp_color.getY() * 255);
			int b = (int)(tmp_color.getZ() * 255);
			window->setPixel(x, y, r, g, b);
		}
	}
}

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR lpCmdLine, int nCmdShow) {
	RenderWindow mainWindow(hInstance, nCmdShow);
	Camera cam( Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 1.0f), 1024, 768);
	Scene scene = Scene();
	scene.getLights()->push_back(new Light(Vec3(-10.0f, 0.0f, 0.0f), 1.0f, 1.0f, 1.0f));

	scene.getSceneObjects()->push_back(new Sphere(Vec3(-0.23f, 0.5f, 5.0f), 1.08f, Material(1.05f)));
	scene.getSceneObjects()->push_back(new Sphere(Vec3(1.0f, 2.0f, 8.f), 1.0f, Material(0.2f, 1.0f, 1.0f, 1000.0f, Color(255, 0, 0))));
	scene.getSceneObjects()->push_back(new Sphere(Vec3(-2.0f, 1.5f, 7.0f), 1.0f, Material(0.2f, 1.0f, 1.0f, 1000.0f, Color(200, 50, 100))));
	scene.getSceneObjects()->push_back(new Sphere(Vec3(-2.0f, -1.5f, 7.0f), 1.0f, Material(0.2f, 1.0f, 1.0f, 1000.0f, Color(0, 200, 200))));

	Material mWall = Material(1.0f, 1.0f, 1.0f, 1.0f, Color(120, 40, 10), "Maps/wall_HD_1_bump.ppm");
	scene.getSceneObjects()->push_back(new Planar(Vec3(2.0f, 1.0f, 10.0f), Vec3(6.0f, 0.0f, -3.0f), Vec3(0.0f, 6.0f, 0.0f), mWall));
	scene.getSceneObjects()->push_back(new Planar(Vec3(-6.0f, 1.0f, 10.0f), Vec3(6.0f, 0.0f, 3.0f), Vec3(0.0f, 6.0f, 0.0f), mWall));
	
	thread renderThread(renderingLoop, &mainWindow, &cam, scene);

	MSG msg = {};
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	renderThread.join();

	return msg.wParam;
}