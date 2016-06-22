/**
* \author Marie DARRIGOL & Anthony LEONARD & Ophélie PELLOUX-PRAYER & Olivier SOLDANO
* \project Ray-Tracing
* \file Mat3.cpp
* \brief 3 by 3 matrix of floats
*/
#include "Mat3.h"

Mat3::Mat3(const float(&data)[3][3]) {
	this->data[0][0] = data[0][0];
	this->data[0][1] = data[0][1];
	this->data[0][2] = data[0][2];
	this->data[1][0] = data[1][0];
	this->data[1][1] = data[1][1];
	this->data[1][2] = data[1][2];
	this->data[2][0] = data[2][0];
	this->data[2][1] = data[2][1];
	this->data[2][2] = data[2][2];
}

Mat3::Mat3() : Mat3({ { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } }) {}

Mat3 Mat3::operator*(const Mat3& m) const {
	float
		m00 = data[0][0] * m.data[0][0] + data[0][1] * m.data[1][0] + data[0][2] * m.data[2][0],
		m01 = data[0][0] * m.data[0][1] + data[0][1] * m.data[1][1] + data[0][2] * m.data[2][1],
		m02 = data[0][0] * m.data[0][2] + data[0][1] * m.data[1][2] + data[0][2] * m.data[2][2],

		m10 = data[1][0] * m.data[0][0] + data[1][1] * m.data[1][0] + data[1][2] * m.data[2][0],
		m11 = data[1][0] * m.data[0][1] + data[1][1] * m.data[1][1] + data[1][2] * m.data[2][1],
		m12 = data[1][0] * m.data[0][2] + data[1][1] * m.data[1][2] + data[1][2] * m.data[2][2],

		m20 = data[2][0] * m.data[0][0] + data[2][1] * m.data[1][0] + data[2][2] * m.data[2][0],
		m21 = data[2][0] * m.data[0][1] + data[2][1] * m.data[1][1] + data[2][2] * m.data[2][1],
		m22 = data[2][0] * m.data[0][2] + data[2][1] * m.data[1][2] + data[2][2] * m.data[2][2];

	return Mat3({ { m00, m01, m02 }, { m10, m11, m12 }, { m20, m21, m22 } });
}

Mat3 Mat3::operator+(const Mat3& m) const {
	float
		m00 = data[0][0] + m.data[0][0],
		m01 = data[0][1] + m.data[0][1],
		m02 = data[0][2] + m.data[0][2],

		m10 = data[1][0] + m.data[1][0],
		m11 = data[1][1] + m.data[1][1],
		m12 = data[1][2] + m.data[1][2],

		m20 = data[2][0] + m.data[2][0],
		m21 = data[2][1] + m.data[2][1],
		m22 = data[2][2] + m.data[2][2];

	return Mat3({ { m00, m01, m02 }, { m10, m11, m12 }, { m20, m21, m22 } });
}

Mat3 Mat3::operator*(const float k) const {
	float
		m00 = data[0][0]*k,
		m01 = data[0][1]*k,
		m02 = data[0][2]*k,

		m10 = data[1][0]*k,
		m11 = data[1][1]*k,
		m12 = data[1][2]*k,

		m20 = data[2][0]*k,
		m21 = data[2][1]*k,
		m22 = data[2][2]*k;

	return Mat3({ { m00, m01, m02 }, { m10, m11, m12 }, { m20, m21, m22 } });
}

Vec3 Mat3::operator*(const Vec3& v) const {
	float
		x = data[0][0] * v.getX() + data[0][1] * v.getY() + data[0][2] * v.getZ(),
		y = data[1][0] * v.getX() + data[1][1] * v.getY() + data[1][2] * v.getZ(),
		z = data[2][0] * v.getX() + data[2][1] * v.getY() + data[2][2] * v.getZ();

	return Vec3(x, y, z);
}