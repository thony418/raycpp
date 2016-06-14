#include "Sphere.h"

pair<bool, Position> Sphere::intersect(Ray &ray){
	Position impact_point = ray.getOrigin();

	// distance between ray origin and center of the sphere
	Position dist = ray.getOrigin() - position;
	// square of the distance
	float squard_dist = dist.scalar_product(dist);

	// if the square dist is less than the square radius of the sphere : consider as no intersection existing 
	if (squard_dist <= pow(radius, 2)){
		// ray origin is on the sphere
		return pair<bool, Position>(false, impact_point);
	}

	// solution for quatratic equation
	float t0, t1;

	// calcul coefficient
	float a = ray.getDirection().scalar_product(ray.getDirection());

	return pair<bool, Position>(true, impact_point);
}