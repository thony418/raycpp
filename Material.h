#pragma once

class Material{
public:
	Material();
	Material(float amb, float diff, float spec);
private:
	float phong_ambiant_factor, phong_diffuse_factor, phong_specular_factor, phong_specular_alpha ;
};