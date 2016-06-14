#pragma once
#include "Position.h"
#include "Vec3.h"

class Ray{
public:
	Position getOrigin(){ return origin; };
	Vec3 getDirection(){ return direction; };
private:
	Position origin;
	Vec3 direction;
};