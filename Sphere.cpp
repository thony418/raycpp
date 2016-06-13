#include "Sphere.h"

pair<bool, Position> Sphere::intersect(Ray &ray){
	Position impact_point = ray.getOrigin();

	// distance between ray origin and center of the sphere
	Position dist = ray.getOrigin() - position;
	// square of the distance
	float squard_dist = dist.scalar_product(dist);

	// ray origin is on the sphere
	if (squard_dist <= pow(radius, 2)){
		return pair<bool, Position>(false, impact_point);
	}

	return pair<bool, Position>(true, impact_point);
}