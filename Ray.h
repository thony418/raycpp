#pragma once
#include "Vec3.h"
#include "Material.h"
#include "Light.h"
#include "Color.h"

class Ray{
public:
	Ray(Vec3 pOrigin, Vec3 vDir);
	inline Vec3 getOrigin(){ return origin; };
	inline Vec3 getDirection(){ return direction; };
	Color phong_ambiant(Material &mat, Light &light);
	Color phong_diffuse(Vec3 &collision_point, Vec3 &norm, Material &mat, Light &light);
	Color phong_specular(Vec3 &collision_point, Vec3 &norm, Material &mat, Light &light);
	Color phong_shading(Vec3 &collision_point, Vec3 &norm, Material &mat, Light &light);
private:
	Vec3 origin;
	Vec3 direction;
	int ttl;
};