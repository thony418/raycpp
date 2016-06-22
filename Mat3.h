/**
* \author Marie DARRIGOL & Anthony LEONARD & Ophélie PELLOUX-PRAYER & Olivier SOLDANO
* \project Ray-Tracing
* \file Mat3.h
* \brief 3 by 3 matrix of floats
*/

#pragma once
#include "Vec3.h"
class Mat3 {
private:
	float data[3][3];
public:
	Mat3(const float (&data)[3][3]);
	Mat3();

	// Matrix multiplication
	Mat3 operator*(const Mat3& m) const;
	Vec3 operator*(const Vec3& v) const;
	
	// Multiply each component by k
	Mat3 operator*(const float k) const;
	
	// Matrix addition
	Mat3 operator+(const Mat3& m) const;
};

inline Mat3 operator*(const float k, const Mat3& m) { return m*k; };

const Mat3 I3({ { 1.0f, 0.0f, 0.0f }, { 0.0f, 1.0f, 0.0f }, { 0.0f, 0.0f, 1.0f } });
