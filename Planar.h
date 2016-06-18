#pragma once
#include "SceneObject.h"

class Planar : public SceneObject{
public:
	
	virtual pair<bool, Vec3> intersect(Ray &ray);
private:
	Vec3 n;
};