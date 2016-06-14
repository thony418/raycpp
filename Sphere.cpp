#include "Sphere.h"

pair<bool, Vec3> Sphere::intersect(Ray &ray){
	Vec3 impact_point = ray.getOrigin();

	// distance between ray origin and center of the sphere
	Vec3 dist = ray.getOrigin() - position;
	// square of the distance
	float squard_dist = dist * dist;

	float squard_radius = radius * radius;

	// if the square dist is less than the square radius of the sphere : consider as no intersection existing 
	if (squard_dist <= squard_radius){
		// ray origin is on the sphere
		return pair<bool, Vec3>(false, impact_point);
	}

	// solution for quatratic equation
	float t0, t1;

	// calcul coefficient
	float a = ray.getDirection() * ray.getDirection();  // a = direction * direction
	float b = ray.getDirection() * dist * 2.0f; // 2.0 * direction *  (origin - center)
	float c = squard_dist - squard_radius;

	// calcul discriminant
	float discr = b * b - 4.0f * a * c;

	if (discr < 0){ 
		// no intersection
		return pair<bool, Vec3>(false, impact_point);
	}
	else { 
		// one or two intersection
		float sqrt_discr = sqrtf(discr);
		t0 = (-b - sqrt_discr) / (2.0f * a);
		t1 = (-b + sqrt_discr) / (2.0f * a);
	}

	if (t1 < 0){
		// no intersection : the ray's origin is after the sphere
		return pair<bool, Vec3>(false, impact_point);
	}
	else{
		// intersection: t0 and t1 > 0, t0 can be equal to t1
		impact_point = ray.getOrigin() + ray.getDirection() * t0;// p = origin + t0 * direction
		return pair<bool, Vec3>(true, impact_point);
	}
}