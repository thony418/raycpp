#include "Planar.h"

// Will create a planar at 0, 0, 0 with a side of 2
Planar::Planar() {
	this->position = Vec3(0, 0, 0);
	this->halfWidth = Vec3(1, 0, 0);
	this->halfHeight = Vec3(0, 1, 0);
	this->n = (this->halfWidth^this->halfHeight).unit();
}

// Constructor with all the parameters
Planar::Planar(Vec3 pos, Vec3 w, Vec3 h) {
	this->position = pos;
	this->halfWidth = w;
	this->halfHeight = h;
	this->n = (this->halfWidth^this->halfHeight).unit();
}

pair<bool, Vec3> Planar::intersect(Ray &ray){
	// declare the impact point
	Vec3 impact_point = ray.getOrigin();

	// normalize the vector (n is already normalized)
	Vec3 l0 = ray.getOrigin();
	Vec3 l = ray.getDirection().unit();
	Vec3 p0 = position;

	// calcul the denominator
	float denom = n * l;
	// if the ray and the normal vector of the planar isn't parallel
	if (denom > 1e-6) {
		// calcul t for determinate if the ray intersect the planar
		float t = ((p0-l0) * n) / denom;
		// calcul the impact point
		impact_point = l0 + l * t;
		// verif if the impact point is in the square
		if (impact_point.getX() < maxCoordinates().getX() && impact_point.getX() > minCoordinates().getX()
			&& impact_point.getY() < maxCoordinates().getY() && impact_point.getY() > minCoordinates().getY() 
			/*&& impact_point.getZ() <= maxCoordinates().getZ() && impact_point.getZ() >= minCoordinates().getZ()*/){
				return pair<bool, Vec3>(t >= 0, impact_point);
		}
		else{
			return pair<bool, Vec3>(false, impact_point);
		}
	}
	return pair<bool, Vec3>(false, impact_point);
}

Vec3 Planar::minCoordinates() {
	float x = halfWidth.getX() > halfHeight.getX() ? halfWidth.getX() : halfHeight.getX();
	float y = halfWidth.getY() > halfHeight.getY() ? halfWidth.getY() : halfHeight.getY();
	float z = halfWidth.getZ() > halfHeight.getZ() ? halfWidth.getZ() : halfHeight.getZ();
	return Vec3(position.getX() - x, position.getY() - y, position.getZ() - z);
}

Vec3 Planar::maxCoordinates() {
	float x = halfWidth.getX() > halfHeight.getX() ? halfWidth.getX() : halfHeight.getX();
	float y = halfWidth.getY() > halfHeight.getY() ? halfWidth.getY() : halfHeight.getY();
	float z = halfWidth.getZ() > halfHeight.getZ() ? halfWidth.getZ() : halfHeight.getZ();
	return Vec3(position.getX() + x, position.getY() + y, position.getZ() + z);
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