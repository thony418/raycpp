/**
*\file Color.h
*\brief subclass of Vec3 for describing simple RGB colors (no alpha)
*\author Olivier SOLDANO
*/

#pragma once
#include "Vec3.h"
class Color : public Vec3 {
public:
	Color();
	Color(float r, float g, float b);
	Color(const Vec3 &c);
	Color::Color(int r, int g, int b);
	void normalise(void);
	~Color();
};

