#pragma once
#include "Position.h"

class Ray{
public:
	Position getOrigin(){ return origin; };
private:
	Position origin;
};