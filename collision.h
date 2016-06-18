#pragma once
#include "Ray.h"
#include "Scene.h"

	/**
	 * Determine the best scene objet collide
	 * return : impact point and the best scene object collide
	 * if not object was collide return ray's origin and nullptr
	**/
	pair<Vec3, SceneObject*> collide(Ray &ray, vector<SceneObject*>* sceneObjects);
	pair<Vec3, SceneObject*> collide(Ray &ray, Scene &scene);