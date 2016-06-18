#include "Planar.h"

// Will create a planar at 0, 0, 0 with a side of 2
Planar::Planar() {
	this->position = Vec3(0, 0, 0);
	this->halfWidth = Vec3(1, 0, 0);
	this->halfHeight = Vec3(0, 1, 0);
	this->n = this->halfHeight^this->halfWidth;	// n = 0, 0, -1 so it will face the camera if it is in the z direction
}

// Constructor with all the parameters
Planar::Planar(Vec3 pos, Vec3 w, Vec3 h) {
	this->position = pos;
	this->halfWidth = w;
	this->halfHeight = h;
	this->n = this->halfHeight^this->halfWidth;
}

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
		if (impact_point.getX() < halfWidth.getX() && impact_point.getX() > -halfWidth.getX() 
			&& impact_point.getY() < halfHeight.getY() && impact_point.getY() > -halfHeight.getY()){
			return pair<bool, Vec3>(t >= 0, impact_point);
		}
		else{
			return pair<bool, Vec3>(false, impact_point);
		}
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

	// Normalized x and y, to be multiply with the size of the map
	float xNorm = 1 + this->halfWidth.unit()*impactPositionOnObject.unit();
	float yNorm = 1 + this->halfHeight.unit()*impactPositionOnObject.unit();
	// TODO: use x and y to get the matching point on the bump map

	// TODO : compute the normal with the color found on the map at the impact's coordinates

	return res;
}