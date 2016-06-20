#include "Material.h"

Material::Material(){
	phong_ambiant_factor = 0.0f;
	phong_diffuse_factor = 0.0f;
	phong_specular_factor = 0.0f;
	color = Vec3();
}

Material::Material(float amb, float diff, float spec, Color color): phong_ambiant_factor(amb),
																   phong_diffuse_factor(diff),
																   phong_specular_factor(spec),
																   color(color){}
