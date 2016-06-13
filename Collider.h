#pragma once
#include "Ray.h"
#include "Scene.h"

class Collider{
public:
	/**
	 * Determine the best scene objet collide
	 * return : impact point and the best scene object collide
	 * if not object was collide return ray's origin and nullptr
	**/
	pair<Position, SceneObject*> collide(Ray &ray, vector<SceneObject*>* sceneObjects);
	pair<Position, SceneObject*> collide(Ray &ray, Scene &scene); 
};