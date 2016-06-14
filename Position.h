#pragma once
#include <math.h>
#include <numeric>
#include <vector>

using namespace std;

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
	/**
	 * Distance between this and the otherPosition
	 * Equation : dist = sqrt(pow(x2 − x1,2)+pow(y2 − y1, 2) + pow(z2 − z1, 2))
	**/
	float dist(Position &otherPosition);

	/**
	* Dot or scalar product between this and the otherPosition
	**/
	float scalar_product(Position &otherPosition);

	float getX(){ return x; };
	float getY(){ return y; };
	float getZ(){ return z; };
	void setX(float newX){ x = newX; };
	void setY(float newY){ y = newY; };
	void setZ(float newZ){ z = newZ; };

	friend Position operator-(Position &p1, Position &p2);
	friend Position operator-(Position &p1, Position &p2);
private:
	float x;
	float y;
	float z;
};