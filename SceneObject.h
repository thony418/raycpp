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
	
	// Used to compute the bump of the object on the impact point if it has a bump map
	inline Vec3 computeBump(const Vec3& impact) const { return Vec3(); };

	Vec3 getPosition() const { return position; };
protected:
	Vec3 position;
	Material material;
};