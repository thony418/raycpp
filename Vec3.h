/**
* \author Marie DARRIGOL & Anthony LEONARD & Ophélie PELLOUX-PRAYER & Olivier SOLDANO
* \project Ray-Tracing
* \file Vec3.h
* \brief Represent a vector a 3 float, either a true vector, a position or a color.
*/

#pragma once
#include <vector>
#include <numeric>

using namespace std;

class Vec3 {
private:
	float x, y, z;
public:
	Vec3();
	Vec3(const float x, const float y, const float z);
	Vec3(const Vec3& v);
	Vec3(const Vec3& v1, const Vec3 &v2);

	// Multiply or divide each component
	Vec3 operator*(const float a) const;
	Vec3 operator/(const float a) const;
	
	// Scalar product
	float operator*(const Vec3& v) const;


	Vec3 operator+(const Vec3& v) const;
	Vec3 operator+(const float a) const;
	Vec3 operator-(const Vec3& v) const;
	Vec3 operator-() const;

	// Cross product
	Vec3 operator^(const Vec3& v) const;

	// Length of a vector
	float length() const;

	// Return the normalized vector
	Vec3 unit() const;

	Vec3 reflect(Vec3 &norm);
	Vec3 refract(Vec3 &norm, float index_incom, float index_outgo);

	// getters and setters
	inline float getX() const { return x; };
	inline float getY() const { return y; };
	inline float getZ() const { return z; };
	inline void setX(float x) { this->x = x; };
	inline void setY(float y) { this->y = y; };
	inline void setZ(float z) { this->z = z; };
};

inline Vec3 operator*(const float k, const Vec3& v) { return v*k; }
