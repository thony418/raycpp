#pragma once
#include "SceneObject.h"

class Planar : public SceneObject{
public:
	/**
	 * Determine the intersection between a ray and a planar
	 * Solution Geometric : p = l0 + t * l
	 * Solution Analytic : t = (p0 - l0).n / (l.n)
	 * return : false and the ray's origin if no intersection and true and the impact point if intersection
	 * base on http://www.scratchapixel.com/lessons/3d-basic-rendering/minimal-ray-tracer-rendering-simple-shapes/ray-plane-and-ray-disk-intersection
	**/
	virtual pair<bool, Vec3> intersect(Ray &ray);
private:
	Vec3 n;
};