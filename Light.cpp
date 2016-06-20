#include "Light.h"

Light::Light():position(Vec3(10.0f,10.0f,10.0f)), ambiant(1.0f), diffuse(1.0f), specular(1.0f){}
Light::Light(Vec3 position, float ambiant, float diffuse, float specular):	position(position),
																			ambiant(ambiant),
																			diffuse(diffuse),
																			specular(specular){}
