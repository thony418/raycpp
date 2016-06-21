#include "Color.h"
#include <algorithm>

/**
*\fn Color::Color()
*\brief constructs a RGB color descriptor that is perfectly black
*/
Color::Color() : Vec3() {}

/**
*\fn Color::Color(float r, float g, float b)
*\brief constructs a RGB color descriptor with r,g, and b in [0.0 , 1.0]
*/
Color::Color(float r, float g, float b): Vec3(r,g,b){}

/**
*\fn Color::Color(int r, int g, int b)
*\brief constructs a RGB color descriptor with r,g, and b integers and in [0;255]
	reducing those standard integer values to the float range [0.0 , 1.0]
*/
Color::Color(int r, int g, int b) : Vec3(((float) r) / 255.0f,
										 ((float) g) / 255.0f,
									     ((float) b) / 255.0f) {}


/**
*\fn Color::Color(const Vec3 &c)
*\brief copy constructor
*/
Color::Color(const Vec3 &c): Vec3(c){}


/**
*\fn void Color::normalise()
*\brief corrects the overflows
*/
void Color::normalise() {
	float max_overflow = max(max(this->getX(), this->getY()), this->getZ());
	if (max_overflow > 1.0f) {
		this->setX(this->getX() / max_overflow);
		this->setY(this->getY() / max_overflow);
		this->setZ(this->getZ() / max_overflow);
	}
}

Color::~Color(){}
