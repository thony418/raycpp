#pragma once
#include "Ray.h"
#include "Scene.h"

class Collider{
public:
	Position collide(Ray &ray, Scene &scene); // changer position par pair<Position,SceneObject> ? 
};