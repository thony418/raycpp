#pragma once
#include "Position.h"
#include "Material.h"
#include "Ray.h"

using namespace std;

class SceneObject{
public:
	/**
	 * Determine if the ray have an intersection to the scene object
	 * return: true and the impact point if intersect, false and origin of the ray if not intersect 
	**/
	pair<bool, Position> intersect(Ray &ray){ return pair<bool, Position>(false, ray.getOrigin()); };
	Position getPosition(){ return position; }
private:
	Position position;
	Material material;
};