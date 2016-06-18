/*
	Module used to compute the bump effect on an object
	Takes the impact and the object return by the Collider
	If the object exists and has a bump map, will return a Vec3 that represents the normal on that point
	Else, will return the standard normal on this point
	This normal will be used by the Phong model
*/

#pragma once
#include "SceneObject.h"
#include "Vec3.h"

class BumpMapping {
public:
	Vec3 computeBump(const pair<Vec3, SceneObject*> impactedObject) const;
};