#pragma once
#include "Vec3.h"

class Light{
public:
	Vec3 getPosition(){ return position; };
private:
	Vec3 position;
};