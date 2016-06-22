/**
* \author Marie DARRIGOL & Anthony LEONARD & Ophélie PELLOUX-PRAYER & Olivier SOLDANO
* \project Ray-Tracing
* \class Box.cpp
* \brief Box object  
*/
#include "Box.h"
#include <algorithm> 

pair<bool, Vec3> Box::intersect(Ray &ray){
	float tmin = (minCoordinates().getX() - ray.getOrigin().getX()) / ray.getDirection().getX();
	float tmax = (maxCoordinates().getX() - ray.getOrigin().getX()) / ray.getDirection().getX();

	if (tmin > tmax) swap(tmin, tmax);

	float tymin = (minCoordinates().getY() - ray.getOrigin().getY()) / ray.getDirection().getY();
	float tymax = (maxCoordinates().getY() - ray.getOrigin().getY()) / ray.getDirection().getY();

	if (tymin > tymax) swap(tymin, tymax);

	if ((tmin > tymax) || (tymin > tmax))
		return pair<bool, Vec3>(false, ray.getOrigin());

	tmin = min(tymin, tmin);
	tmax = min(tymax, tmax);

	float tzmin = (minCoordinates().getZ() - ray.getOrigin().getZ()) / ray.getDirection().getZ();
	float tzmax = (maxCoordinates().getZ() - ray.getOrigin().getZ()) / ray.getDirection().getZ();

	if (tzmin > tzmax) swap(tzmin, tzmax);

	if ((tmin > tzmax) || (tzmin > tmax))
		return pair<bool, Vec3>(false, ray.getOrigin());

	tmin = min(tzmin, tmin);
	tmax = min(tzmax, tmax);

	if (tmin < 0){
		return pair<bool, Vec3>(true, ray.getOrigin() + ray.getDirection() * tmax);
	}
	return pair<bool, Vec3>(true, ray.getOrigin() + ray.getDirection() * max(tmin, 0.0f));
}

Vec3 Box::computeBump(const Vec3& impact) const {
	Vec3 res = (-impact - this->position);	// standard normal on the impact point
	return res;
}