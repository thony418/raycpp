#include "Position.h"

float Position::dist(Position &otherPosition){
	return sqrtf(powf(otherPosition.getX() - x, 2) + powf(otherPosition.getY() - y, 2) + powf(otherPosition.getZ() - z, 2));
}

float Position::scalar_product(Position &otherPosition){
	vector<float> this_vector = { x, y, z };
	vector<float> other_vector = { otherPosition.getX(), otherPosition.getY(), otherPosition.getZ()};
	return inner_product(this_vector.begin(), this_vector.end(), other_vector.begin(), 0.0f);
}
 
Position operator-(Position &p1, Position &p2){
	return Position(p1.getX() - p2.getX(), p1.getY() - p2.getY(), p1.getZ() - p2.getZ());
}

Position operator+(Position &p1, Position &p2){
	return Position(p1.getX() + p2.getX(), p1.getY() + p2.getY(), p1.getZ() + p2.getZ());
}