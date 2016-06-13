#pragma once
#include <vector>
#include <stdlib.h>
#include "Light.h"
#include "SceneObject.h"

class Scene{
public:
	vector<SceneObject*>* getSceneObjects(){ return sceneObjects; };
private: 
	vector<SceneObject*>* sceneObjects;
	vector<Light*>* lights;
};
