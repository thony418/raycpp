#pragma once
#include "Vec3.h"
#include "Material.h"
#include "Light.h"
#include "Color.h"
#define RAY_TTL 1

class Scene;
class SceneObject;


class Ray{
public:
	Ray(Vec3 pOrigin, Vec3 vDir, int ttl);
	inline Vec3 getOrigin(){ return origin; };
	inline Vec3 getDirection(){ return direction; };
	Color phong_ambiant(Material &mat, Scene & scene);
	Color phong_diffuse(Vec3 &collision_point, Vec3 & norm, Material & mat, Scene & scene);
	Color phong_specular(Vec3 &collision_point, Vec3 & norm, Material & mat, Scene & scene);
	Color phong_shading(Scene & scene);
private:
	Vec3 origin;
	Vec3 direction;
	int ttl;///< time to live of the ray (number of reflections possible for this Ray) 
};