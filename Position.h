#pragma once

class Position{
public:
	Position(){
		x = 0;
		y = 0;
		z = 0;
	};
	Position(float x, float y, float z){
		this->x = x;
		this->y = y;
		this->z = z;
	};
	float dist(Position otherPosition){ return 0.0; };
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