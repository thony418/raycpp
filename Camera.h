#pragma once
#include "Vec3.h"
#include "Mat3.h"
#include "Ray.h"
class Camera
{
private:
	Vec3 pOrigin;
	unsigned int picWidth, picHeight;

	// Les données suivantes sont des données calculées
	Mat3 R; // Matrice de rotation permettant d'orienter la grille
	float distToFrame; // Distance de l'observateur à la grille
	float width, height; // Dimensions de la grille (<= 1.0f)

public:
	Camera(const Vec3& pOrigin, const Vec3& vFrame, const unsigned int picWidth, const unsigned int picHeight);
	Ray getRay(const unsigned int x, const unsigned int y) const;
};

