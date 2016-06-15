#pragma once
#include "Vec3.h"
class Mat3 {
private:
	float data[3][3];
public:
	Mat3(const float (&data)[3][3]);
	Mat3();

	Mat3 operator*(const Mat3& m) const;
	Mat3 operator*(const float k) const;
	Vec3 operator*(const Vec3& v) const;

	Mat3 operator+(const Mat3& m) const;
};

inline Mat3 operator*(const float k, const Mat3& m) { return m*k; };

const Mat3 I3({ { 1.0f, 0.0f, 0.0f }, { 0.0f, 1.0f, 0.0f }, { 0.0f, 0.0f, 1.0f } });
