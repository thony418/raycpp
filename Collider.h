#pragma once
#include "Ray.h"
#include "Scene.h"

class Collider{
public:
	Position collide(Ray rayon, Scene scene); // changer position par paire position sceneObject ? 
};