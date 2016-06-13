#pragma once

class Vector{
	Vector(){
		x = 0;
		y = 0;
		z = 0;
	};
	Vector(float x, float y, float z){
		this->x = x;
		this->y = y;
		this->z = z;
	};
	float getX(){ return x; };
	float getY(){ return y; };
	float getZ(){ return z; };
	void setX(float newX){ x = newX; };
	void setY(float newY){ y = newY; };
	void setZ(float newZ){ z = newZ; };
private:
	float x;
	float y;
	float z;
};