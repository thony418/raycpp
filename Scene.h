#pragma once
#include <vector>
#include <stdlib.h>
#include "Light.h"
#include "SceneObject.h"

using namespace std;

class Scene{
	vector<SceneObject*>* getSceneObjects(){ return sceneObjects; };
private: 
	vector<SceneObject*>* sceneObjects;
	vector<Light*>* lights;
};
