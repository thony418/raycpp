#pragma once
#include "Material.h"
#include "Ray.h"
#include <utility>

using namespace std;

class SceneObject{
public:
	/**
	 * Determine if the ray have an intersection to the scene object
	 * return: true and the impact point if intersect, false and origin of the ray if not intersect 
	**/
	pair<bool, Vec3> intersect(Ray &ray){ return pair<bool, Vec3>(false, ray.getOrigin()); };
	Vec3 getPosition(){ return position; };
protected:
	Vec3 position;
	Material material;
};