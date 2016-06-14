#pragma once
#include "Vec3.h"

class Ray{
public:
	Ray(Vec3 pOrigin, Vec3 vDir);
	Vec3 getOrigin(){ return origin; };
	Vec3 getDirection(){ return direction; };
private:
	Vec3 origin;
	Vec3 direction;
};