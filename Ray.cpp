#include "Ray.h"
#include "SceneObject.h"
#include "Scene.h"
#include "Octree.h"
#include "collision.h"
#include <algorithm>

Ray::Ray(Vec3 pOrigin, Vec3 vDir, int ttl) : origin(pOrigin), direction(vDir), ttl(ttl) {}


/**
*\fn Color Ray::phong_ambiant(Material &mat, Light &light)
*\brief phong's ambiant reflection of this Ray, according to the Material of the collided SceneObject
*		and its Lighting.
*\return a new Color giving the RGB color componants each range between 0.0f and 1.0f
*/
Color Ray::phong_ambiant(Material &mat, Scene & scene){
	Color ambiant_color;
	for (int i = 0; i < (int)scene.getLights()->size(); i++) {
		ambiant_color = ambiant_color * (float) i + Color(	mat.get_color() * (mat.get_phong_ambiant() *
															scene.getLights()->at(i)->get_ambiant()));
	}
	ambiant_color.normalise();
	return ambiant_color;
}


/**
*\fn float lambertian(Vec3 &collision_point, Vec3 &normal, Light &light)
*\brief express the lambertian coefficient describing the self shadowing due to the inclination
	toward light of a point on a SceneObject
*\return a float representing this factor, 
*/
float lambertian(Vec3 &collision_point, Vec3 &normal, Vec3 &light_direction) {
	float lambert = normal * light_direction;
	return (lambert > 0.0f) ? lambert : 0.0f;
}

/**
*\fn Color Ray::phong_diffuse(Vec3 &collision_point, Vec3 &norm, Material &mat, Light &light)
*\brief phong's diffuse reflection of this Ray, according to the normal vector of the collided SceneObject
*		and its Material.
*\return a new Color giving the RGB color componants each range between 0.0f and 1.0f
*/
Color Ray::phong_diffuse(Vec3 &collision_point, Vec3 & norm, Material & mat, Scene & scene, Octree &octree) {
	Color diffuse_color = Color();
	Vec3 light_direction;
	Light *curr_light;
	pair<Vec3, SceneObject*> light_intersect;
	for (int i = 0; i < (int)scene.getLights()->size(); i++) {
		curr_light = scene.getLights()->at(i);
		light_direction = Vec3(collision_point, curr_light->getPosition()).unit();
		light_intersect = octree.collide(Ray(collision_point, light_direction, 0));
		//light_intersect = collide(Ray(collision_point, light_direction, 0), (*scene.getSceneObjects()));

		if (light_intersect.second == nullptr || light_intersect.second->getMaterial().is_transparent()) {
			diffuse_color = (diffuse_color * (float)i) + Color(mat.get_color() * mat.get_phong_diffuse() * curr_light->get_diffuse() *
																lambertian(collision_point, norm, light_direction)
																);
			diffuse_color = diffuse_color / ((float)(i + 1));

		}
	}
	diffuse_color.normalise();
	return diffuse_color;
}

/**
*\fn Color Ray::phong_specular(Vec3 &collision_point, Vec3 &norm, Material &mat, Light &light)
*\brief phong's specular reflection of this Ray, according to the normal vector of the collided SceneObject
*		and its Material.
*\return a new Color giving the RGB color componants each range between 0.0f and 1.0f
*/
Color Ray::phong_specular(Vec3 &collision_point, Vec3 & norm, Material & mat, Scene & scene, Octree &octree) {
	Color specular_color = Color();
	Vec3 light_direction, reflected_light;
	Light *curr_light;
	pair<Vec3, SceneObject*> light_intersect, reflect_intersect;

	for (int i = 0; i < (int)scene.getLights()->size(); i++) { // for each light in the scene, combine shadings for the current ray
		curr_light = scene.getLights()->at(i);
		light_direction = Vec3(collision_point, curr_light->getPosition()).unit();
		light_intersect = octree.collide(Ray(collision_point, light_direction, 0));
		//light_intersect = collide(Ray(collision_point, light_direction, 0), (*scene.getSceneObjects()));
		if (light_intersect.second == nullptr || Vec3(light_intersect.first, collision_point).length() > 0.05f || mat.is_transparent()) {
			reflected_light = (-light_direction).reflect(norm);
			specular_color = (specular_color * (float)i) + (Color(	curr_light->get_color() * mat.get_phong_specular() * curr_light->get_specular() *
																	pow(max(reflected_light * this->direction, 0.0f),
																	mat.get_phong_alpha())
																	));
			specular_color = specular_color / ((float)(i + 1));
		}
	}
	specular_color.normalise();
	return specular_color;
}


/*
*\fn Color Ray::(Vec3 &collision_point, Vec3 & norm, Material & mat, Scene & scene)
*\brief calculate the color of a ray pointing to a particular collision point, according to Phong's model shading.
*\return the RGB color resulting of the Phong shading
*/
Color Ray::phong_shading(Scene & scene, Octree &octree)
{
	Color amb, dif, spe, composition;

	// collision detection
	pair<Vec3, SceneObject*> intersection = octree.collide(*this);
	//pair<Vec3, SceneObject*> intersection = collide(*this, (*scene.getSceneObjects()));

	//if collision calculate shading
	if (intersection.second != nullptr) {
		//extraction informations of the collision
		Material mat = intersection.second->getMaterial();
		Vec3 collision_point = intersection.first, 
			 norm = intersection.second->computeBump(intersection.first);
		
		spe = phong_specular(collision_point, norm, mat, scene, octree);

		if (!mat.is_transparent()) {
			//calculate phong's components
			amb = phong_ambiant(mat, scene);
			dif = phong_diffuse(collision_point, norm, mat, scene, octree);

			if (this->ttl <= 0) { //if end of life of ray return
				composition = (amb / 3.0f) + (dif / 3.0f) + (spe / 3.0f);
			}
			else { // else combine with reflexion
				Ray reflection = Ray(collision_point, -this->direction.reflect(norm), this->ttl - 1);
				composition =	amb * (0.80f / 3.0f) +
								dif * (0.80f / 3.0f) + 
								spe * (0.80f / 3.0f) + 
								mat.get_phong_specular() * reflection.phong_shading(scene, octree) * 0.2f;
			}
		} else { //if ray enconters transparent object
			if (this->ttl <= 0) { 
				composition = spe;
			} else {
				Ray refract = Ray(collision_point, this->direction.refract(norm, 1.0f, mat.get_refractive_index()), this->ttl-1);
				composition = spe + refract.phong_shading(scene, octree);
			}
		}
	// if no collision show scene background color
	} else {
		composition = scene.getBackground();
	}
	composition.normalise();
	return composition;
}