#include "Material.h"

Material::Material():
	phong_ambiant_factor(.2f),
	phong_diffuse_factor (1.0f),
	phong_specular_factor (1.0f),
	phong_specular_alpha(100.0f),
	color(Vec3()),
	bump_map (Image()),
	refractive_index ( 0.0f){}

Material::Material(float ref_index) : Material(){
	refractive_index = ref_index;
}

Material::Material(float amb, float diff, float spec, float alpha, Color color): phong_ambiant_factor(amb),
																				 phong_diffuse_factor(diff),
																				 phong_specular_factor(spec),
																				 phong_specular_alpha(alpha),
																				 color(color),
																				 refractive_index(0.0f){}

Material::Material(float amb, float diff, float spec, float alpha, Color color, float refr) : phong_ambiant_factor(amb),
    																			  phong_diffuse_factor(diff),
																				  phong_specular_factor(spec),
																				  phong_specular_alpha(alpha),
																				  color(color),
																				  refractive_index(refr){}

Material::Material(float amb, float diff, float spec, float alpha, Color color, const char* file):	phong_ambiant_factor(amb),
																									phong_diffuse_factor(diff),
																									phong_specular_factor(spec),
																									phong_specular_alpha(alpha),
																									color(color),
																									bump_map(),
																									refractive_index(0.0f) {
	bump_map.readPPM(file);
}