#pragma once
#include "SceneObject.h"

class Planar : public SceneObject{
public:
	// Default constructor
	Planar();
	// Constructor with all the parameters
	Planar(Vec3 pos, Vec3 w, Vec3 h);

	/**
	 * Determine the intersection between a ray and a planar
	 * Solution Geometric : p = l0 + t * l
	 * Solution Analytic : t = (p0 - l0).n / (l.n)
	 * return : false and the ray's origin if no intersection and true and the impact point if intersection
	 * base on http://www.scratchapixel.com/lessons/3d-basic-rendering/minimal-ray-tracer-rendering-simple-shapes/ray-plane-and-ray-disk-intersection
	**/
	pair<bool, Vec3> intersect(Ray &ray);

	Vec3 minCoordinates();
	Vec3 maxCoordinates();

	// Overridden method to match the planar case
	Vec3 computeBump(const Vec3& impact) const;
private:
	// Normal vector of the planar
	Vec3 n;
	// Half width of the object (beginning at its position)
	Vec3 halfWidth; // x
	// Half height of the object (beginning at its position)
	Vec3 halfHeight; // y
};