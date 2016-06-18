#include "Planar.h"

pair<bool, Vec3> Planar::intersect(Ray &ray){
	// declare the impact point
	Vec3 impact_point = ray.getOrigin();

	// normalize the vector (n is already normalize)
	Vec3 l0 = ray.getOrigin().unit();
	Vec3 l = ray.getDirection().unit();
	Vec3 p0 = position.unit();

	// calcul the denominator
	float denom = n * l;
	// if the ray and the normal vector of the planar isn't parallel
	if (denom > 1e-6) {
		// calcul t for determinate if the ray intersect the planar
		float t = ((p0-l0) * n) / denom;
		// calcul the impact point
		impact_point = l0 + l * t;
		return pair<bool, Vec3>(t >= 0, impact_point);
	}

	return pair<bool, Vec3>(false, impact_point);
}