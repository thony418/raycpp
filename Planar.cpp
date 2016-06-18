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

/*
	Used to compute the normal on the impact point to make the surface "bump"
	Impact point given in the scene base
	If the impacted planar has a bump map, will get the color value of this point on the map
	Then, will compute and return the normal depending on the color found
	Else, will return the normal of the planar
*/
Vec3 Planar::computeBump(const Vec3& impact) const {
	Vec3 res = this->n;
	// TODO : check if the material has a bump map

	Vec3 impactPositionOnObject = impact - this->getPosition();

	// TODO : find the pixel on the map

	// TODO : compute the normal with the color found on the map at the impact's coordinates

	return res;
}