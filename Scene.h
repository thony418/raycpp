#pragma once
#include <vector>
#include <stdlib.h>
#include "Light.h"
#include "SceneObject.h"

using namespace std;

class Scene{
private: 
	vector<SceneObject*> sceneObjects;
	vector<Light*> lights;
};
