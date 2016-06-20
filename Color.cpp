#include "Color.h"

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
	if (this->getX() > 1.0) this->setX(1.0f);
	if (this->getY() > 1.0) this->setY(1.0f);
	if (this->getZ() > 1.0) this->setZ(1.0f);
}

Color::~Color(){}
