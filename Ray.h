#pragma once
#include "Position.h"
#include "Vector.h"

class Ray{
public:
	Position getOrigin(){ return origin; };
private:
	Position origin;
	Vector direction;
};