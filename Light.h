#pragma once
#include "Vec3.h"

class Light{
public:
	Light();
	Light(float ambiant, float diffuse, float specular);
	Vec3 getPosition(){ return position; };
	inline float get_ambiant() { return ambiant; };
	inline float get_diffuse() { return diffuse; };
	inline float get_specular() { return specular; };
private:
	Vec3 position;
	float ambiant, diffuse, specular;
};