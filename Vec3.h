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

	/**
	* Dot or scalar product between this and the otherPosition
	**/
	float scalar_product(Vec3 &other);

	Vec3 operator*(const float a) const;
	float operator*(const Vec3& v) const;

	Vec3 operator+(const Vec3& v) const;

	Vec3 operator^(const Vec3& v) const;

	float length() const;

	Vec3 unit() const;

	inline float getX() const { return x; };
	inline float getY() const { return y; };
	inline float getZ() const { return z; };
};