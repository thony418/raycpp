#include "Vec3.h"
#include <cmath>

Vec3::Vec3() : Vec3(0.0, 0.0, 0.0) {}

Vec3::Vec3(const float x, const float y, const float z) : x(x), y(y), z(z) {}


float Vec3::scalar_product(Vec3 &other){
	vector<float> this_vector = { x, y, z };
	vector<float> other_vector = { other.getX(), other.getY(), other.getZ() };
	return inner_product(this_vector.begin(), this_vector.end(), other_vector.begin(), 0.0f);
}

Vec3 Vec3::operator*(const float a) const { return Vec3(a*x, a*y, a*z); }
float Vec3::operator*(const Vec3& v) const { return sqrtf(x*v.x + y*v.y + z*v.z); }

Vec3 Vec3::operator+(const Vec3& v) const { return Vec3(x + v.x, y + v.y, z + v.z); }

Vec3 Vec3::operator^(const Vec3& v) const { return Vec3(y*v.z - z*v.y, z*v.x - x*v.z, x*v.y - y*v.x); }

float Vec3::length() const { return sqrtf(x*x + y*y + z*z); }

Vec3 Vec3::unit() const { float len = this->length(); return Vec3(x / len, y / len, z / len); }