#include "Light.h"

Light::Light(): ambiant(1.0f), diffuse(1.0f), specular(1.0f){}
Light::Light(float ambiant, float diffuse, float specular): ambiant(ambiant), diffuse(diffuse), specular(specular){}
