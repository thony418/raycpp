#include "Material.h"

Material::Material(){
	phong_ambiant_factor = 0.0f;
	phong_diffuse_factor = 0.0f;
	phong_specular_factor = 0.0f;
	color = Vec3();
	bump_map = Image();
}

Material::Material(float amb, float diff, float spec, float alpha, Color color): phong_ambiant_factor(amb),
																				 phong_diffuse_factor(diff),
																				 phong_specular_factor(spec),
																				 phong_specular_alpha(alpha),
																				 color(color),
																				 bump_map(){}

Material::Material(float amb, float diff, float spec, float alpha, Color color, const char* file):	phong_ambiant_factor(amb),
																									phong_diffuse_factor(diff),
																									phong_specular_factor(spec),
																									phong_specular_alpha(alpha),
																									color(color),
																									bump_map(){
	bump_map.readPPM(file);
}