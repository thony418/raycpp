#pragma once
#include "Vec3.h"
#include "Material.h"

class Ray{
public:
	Ray(Vec3 pOrigin, Vec3 vDir);
	inline Vec3 getOrigin(){ return origin; };
	inline Vec3 getDirection(){ return direction; };
	Vec3 phong_ambiant(Vec3 norm, Material mat);
	Vec3 phong_defuse(Vec3 norm, Material mat);
	Vec3 phong_specular(Vec3 norm, Material mat);
private:
	Vec3 origin;
	Vec3 direction;
	int ttl;
};