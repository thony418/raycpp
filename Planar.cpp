#include "Planar.h"
#include "Color.h"

// Will create a planar at 0, 0, 0 with a side of 2
Planar::Planar() {
	this->position = Vec3(0, 0, 0);
	this->halfWidth = Vec3(1, 0, 0);
	this->halfHeight = Vec3(0, 1, 0);
	this->n = (this->halfWidth^this->halfHeight).unit();
}

// Constructor with all the parameters for the position and size
Planar::Planar(Vec3 &pos, Vec3 &w, Vec3 &h) {
	this->position = pos;
	this->halfWidth = w;
	this->halfHeight = h;
	this->n = (this->halfWidth^this->halfHeight).unit();
}

// Constructor will all the parameters
Planar::Planar(Vec3 &pos, Vec3 &w, Vec3 &h, Material &m) : SceneObject(pos, m){
	this->halfWidth = w;
	this->halfHeight = h;
	this->n = (this->halfWidth^this->halfHeight).unit();
}

pair<bool, Vec3> Planar::intersect(Ray &ray){
	// declare the impact point
	Vec3 impact_point = ray.getOrigin();

	// normalize the vector (n is already normalized)
	Vec3 l0 = ray.getOrigin();
	Vec3 l = ray.getDirection();

	// calcul the denominator
	float denom = l * n;
	// if the ray and the normal vector of the planar isn't parallel
	if (denom > 1e-6) {
		// calcul t for determinate if the ray intersect the planar
		float t = ((position - l0) * n) / denom;
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
	// determine greater x
	float x = halfWidth.getX() > halfHeight.getX() ? halfWidth.getX() : halfHeight.getX();
	// determine greater y
	float y = halfWidth.getY() > halfHeight.getY() ? halfWidth.getY() : halfHeight.getY();
	// determine greater z
	float z = halfWidth.getZ() > halfHeight.getZ() ? halfWidth.getZ() : halfHeight.getZ();
	return Vec3(position.getX() - x, position.getY() - y, position.getZ() - z);
}

Vec3 Planar::maxCoordinates() {
	// determine greater x
	float x = halfWidth.getX() > halfHeight.getX() ? halfWidth.getX() : halfHeight.getX();
	// determine greater y
	float y = halfWidth.getY() > halfHeight.getY() ? halfWidth.getY() : halfHeight.getY();
	// determine greater z
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
	Vec3 res = Vec3() - this->n;
	
	if (this->material.has_bump_map()) {
		Vec3 impactPositionOnObject = impact - this->position;
		unsigned int mapWidth = this->material.get_bump_map_width();
		unsigned int mapHeight = this->material.get_bump_map_height();
		unsigned int halfMapWidth = mapWidth / 2;
		unsigned int halfMapHeight = mapHeight / 2;
		unsigned int x, y;

		// We get the x and y that have been projected on the width and the height of the planar
		float xNorm = impactPositionOnObject * this->halfWidth / this->halfWidth.length();
		float yNorm = impactPositionOnObject * this->halfHeight / this->halfWidth.length();

		// We get the coef to make the map at the scale of the object
		float coefWidth = halfMapWidth / this->halfWidth.length();
		float coefHeight = halfMapHeight / this->halfHeight.length();

		// We compute the delta x and y (in pixels)
		float dx = xNorm * coefWidth;
		float dy = yNorm * coefHeight;

		// We compute the x and y coordinates in float
		float xf = dx + halfMapWidth;
		float yf = dy + halfMapHeight;

		// We convert from float to int
		x = (unsigned int) xf;
		y = (unsigned int) yf;

		// Finally, we get the color at the pixel using the previous coordinates
		Color c = Color();
		if (x >= mapWidth) {
			c = this->material.get_pixel_at((mapWidth-1) + mapWidth*y);
		}else if(y >= mapHeight){
			c = this->material.get_pixel_at(x + mapWidth*(mapHeight-1));
		}else{
			c = this->material.get_pixel_at(x + mapWidth*y);
		}
		res.setX(res.getX() * c.getX());
		res.setY(res.getY() * c.getY());
		res.setZ(res.getZ() * c.getZ());
	}
	
	return res;
}