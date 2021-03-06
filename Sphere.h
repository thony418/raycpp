/**
* \author Marie DARRIGOL & Anthony LEONARD & Oph�lie PELLOUX-PRAYER & Olivier SOLDANO
* \project Ray-Tracing
* \class Sphere.h
* \brief Sphere object 
*/
#pragma once
#include "SceneObject.h"

class Sphere : public SceneObject{
public:
	Sphere(Vec3 p, float radius, Material material) : SceneObject(p, material), radius(radius){
	}

	/**
	 * Determine the ray-sphere intersection
	 * Solution Geometric : P = o+t*d
	 * Solution Analytic : (P-C)^2 - R^2 = 0
	 * (P-C)^2 - R^2 => (o+t*d-C)^2-R^2 => o^2+(td)^2+C^2+2td(o-C)-2oC-R^2
	 * => at^2+bt+c, a = d*d, b = 2d(o-C), c = (o-C)^2-R^2
	 * with : o = ray origin, d = ray direction, C = sphere center, R = sphere radius
	 * base on http://stackoverflow.com/questions/12678225/intersection-problems-with-ray-sphere-intersection
	**/
	pair<bool, Vec3> intersect(Ray &ray);
	
	// Overridden method to match the sphere case
	Vec3 computeBump(const Vec3& impact) const;

	Vec3 minCoordinates(){ return position + (- radius); };
	Vec3 maxCoordinates(){ return position + radius; };
private:
	float radius;
};