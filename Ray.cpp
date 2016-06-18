#include "Ray.h"

Ray::Ray(Vec3 pOrigin, Vec3 vDir) : origin(pOrigin), direction(vDir) {}


/**
*\fn phong_ambiant(Vec3 norm, Material mat)
*\brief phong's ambiant reflection of this Ray, according to the normal vector of the collided SceneObject
*		and its Material.
*\return a new Vec3 giving the RGB color componants each range between 0.0f and 1.0f
*/
Vec3 Ray::phong_ambiant(Vec3 norm, Material mat)
{
	return Vec3();
}

/**
*\fn phong_defuse(Vec3 norm, Material mat)
*\brief phong's diffuse reflection of this Ray, according to the normal vector of the collided SceneObject
*		and its Material.
*\return a new Vec3 giving the RGB color componants each range between 0.0f and 1.0f
*/
Vec3 Ray::phong_diffuse(Vec3 norm, Material mat)
{
	return Vec3();
}


/**
*\fn phong_defuse(Vec3 norm, Material mat)
*\brief phong's specular reflection of this Ray, according to the normal vector of the collided SceneObject
*		and its Material.
*\return a new Vec3 giving the RGB color componants each range between 0.0f and 1.0f
*/
Vec3 Ray::phong_specular(Vec3 norm, Material mat)
{
	return Vec3();
}
