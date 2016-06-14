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
	float a = ray.getDirection().scalar_product(ray.getDirection());  // a = direction * direction
	float b = 2.0f * (ray.getDirection().scalar_product_with_position(dist)); // 2.0 * direction *  (origin - center)
	float c = squard_dist - pow(radius, 2);

	// calcul discriminant
	float discr = b * b - 4.0f * a * c;

	if (discr < 0){ 
		// no intersection
		return pair<bool, Position>(false, impact_point);
	}
	else { 
		// one or two intersection
		float sqrt_discr = sqrtf(discr);
		t0 = (-b - sqrt_discr) / (2.0f * a);
		t1 = (-b + sqrt_discr) / (2.0f * a);
	}

	if (t1 < 0){
		// no intersection : the ray's origin is after the sphere
		return pair<bool, Position>(false, impact_point);
	}
	else{
		// intersection: t0 and t1 > 0, t0 can be equal to t1
		Vec3 distance = ray.getDirection() * t0; // t0 * direction
		impact_point = distance.add_to_position(ray.getOrigin());// p = origin + t0 * direction
		return pair<bool, Position>(true, impact_point);
	}
}