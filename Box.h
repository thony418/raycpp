/**
* \author Marie DARRIGOL & Anthony LEONARD & Ophélie PELLOUX-PRAYER & Olivier SOLDANO
* \project Ray-Tracing
* \class Box.h
* \brief Box object
*/
#pragma once
#include "SceneObject.h"

class Box : public SceneObject{
public:
	Box(Vec3 p, Vec3 min, Vec3 max){
		position = p;
		this->minim = min;
		this->maxim = max;
	}
	
	pair<bool, Vec3> intersect(Ray &ray);

	// Overridden method to match the sphere case
	Vec3 computeBump(const Vec3& impact) const;

	Vec3 minCoordinates(){ return position + minim; };
	Vec3 maxCoordinates(){ return position + maxim; };
private:
	Vec3 minim;
	Vec3 maxim;
};