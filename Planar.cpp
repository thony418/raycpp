#include "Planar.h"

pair<bool, Vec3> Planar::intersect(Ray &ray){
	// declare the impact point
	Vec3 impact_point = ray.getOrigin();

	// assuming vectors are all normalized

	// calcul the denominator
	float denom = n * ray.getDirection();
	// if the ray and the normal vector of the planar isn't parallel
	if (denom > 1e-6) {
		// calcul t for determinate if the ray intersect the planar
		float t = ((position-ray.getOrigin()) * n) / denom;
		// calcul the impact point
		impact_point = ray.getOrigin() + ray.getDirection() * t;
		return pair<bool, Vec3>(t >= 0, impact_point);
	}

	return pair<bool, Vec3>(false, impact_point);
}