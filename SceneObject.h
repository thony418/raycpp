/**
* \author Marie DARRIGOL & Anthony LEONARD & Ophélie PELLOUX-PRAYER & Olivier SOLDANO
* \project Ray-Tracing
* \class SceneObject.h
* \brief virtual class of scene object
*/
#pragma once
#include "Material.h"
#include "Ray.h"
#include <utility>
#include <iostream>

using namespace std;

class SceneObject{
public:

	
	/**
	 * Determine if the ray have an intersection to the scene object
	 * return: true and the impact point if intersect, false and origin of the ray if not intersect 
	**/
	virtual pair<bool, Vec3> intersect(Ray &ray){ return pair<bool, Vec3>(false, ray.getOrigin()); };

	virtual Vec3 minCoordinates() = 0;
	virtual Vec3 maxCoordinates() = 0;
	
	// Used to compute the bump of the object on the impact point if it has a bump map
	virtual Vec3 computeBump(const Vec3& impact) const = 0;

	inline Vec3 getPosition() const { return position; };
	inline Material getMaterial() const { return material; };

	virtual void printSceneObject(){ cout << "simple scene object"; };
protected:
	SceneObject();
	SceneObject(Vec3 &position, Material &material);
	// Represents the center of the object
	Vec3 position;
	Material material;
};