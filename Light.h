#pragma once
#include "Vec3.h"
#include "Color.h"

class Light{
public:
	Light();
	Light(Vec3 position, float ambiant, float diffuse, float specular);
	Vec3 getPosition(){ return position; };
	inline const float get_ambiant() { return ambiant; };
	inline const float get_diffuse() { return diffuse; };
	inline const float get_specular() { return specular; };
	inline const Color get_color() { return color; };
private:
	Vec3 position;
	float ambiant, diffuse, specular;
	Color color;
};