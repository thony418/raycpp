#include "Ray.h"

Ray::Ray(Vec3 pOrigin, Vec3 vDir) : origin(pOrigin), direction(vDir) {}


/**
*\fn Color Ray::phong_ambiant(Material &mat, Light &light)
*\brief phong's ambiant reflection of this Ray, according to the normal vector of the collided SceneObject
*		and its Material.
*\return a new Color giving the RGB color componants each range between 0.0f and 1.0f
*/
Color Ray::phong_ambiant(Material &mat, Light &light){
	Color ambiant_color = mat.get_color() * (mat.get_phong_ambiant() * light.get_ambiant());
	ambiant_color.normalise();
	return ambiant_color;
}


/**
*\fn float lambertian(Vec3 &collision_point, Vec3 &normal, Light &light)
*\brief express the lambertian coefficient describing the self shadowing due to the inclination
	toward light of a point on a SceneObject
*\return a float representing this factor, 
*/
float lambertian(Vec3 &collision_point, Vec3 &normal, Light &light) {
	Vec3 light_vector = Vec3(collision_point, light.getPosition());
	float lambert = abs(normal * light_vector.unit());
	return lambert;
}
/**
*\fn Color Ray::phong_diffuse(Vec3 &collision_point, Vec3 &norm, Material &mat, Light &light)
*\brief phong's diffuse reflection of this Ray, according to the normal vector of the collided SceneObject
*		and its Material.
*\return a new Color giving the RGB color componants each range between 0.0f and 1.0f
*/
Color Ray::phong_diffuse(Vec3 &collision_point, Vec3 &norm, Material &mat, Light &light){
	
	return Color(mat.get_color() * mat.get_phong_diffuse() * light.get_diffuse() * lambertian(collision_point, norm, light));

}

/**
*\fn Color Ray::phong_specular(Vec3 &collision_point, Vec3 &norm, Material &mat, Light &light)
*\brief phong's specular reflection of this Ray, according to the normal vector of the collided SceneObject
*		and its Material.
*\return a new Color giving the RGB color componants each range between 0.0f and 1.0f
*/
Color Ray::phong_specular(Vec3 &collision_point, Vec3 &norm, Material &mat, Light &light){
	return Color();
}


/*
*\fn Color Ray::phong_shading(Vec3 &collision_point, Vec3 & norm, Material & mat, Light & light)
*\brief calculate the color of a ray pointing to a particular collision point, according to Phong's model shading.
*\return the RGB color resulting of the Phong shading
*/
Color Ray::phong_shading(Vec3 &collision_point, Vec3 & norm, Material & mat, Light & light)
{
	Color amb, dif, spe;
	amb = phong_ambiant(mat, light);
	dif = phong_diffuse(collision_point, norm, mat, light);
	spe = phong_specular(collision_point, norm, mat, light);
	return (amb * (1.0f/3.0f)) + (dif * (1.0f/3.0f)) + (spe * (1.0f/3.0f));
}
