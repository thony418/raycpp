#pragma once
#include <vector>
#include <stdlib.h>
#include "Light.h"
#include "SceneObject.h"
#include "Color.h"

class Scene{
public:
	Scene();
	Scene(vector<SceneObject*>* sceneObjects, vector<Light*>* lights, Color background);
	inline vector<SceneObject*>* getSceneObjects(){ return sceneObjects; };
	inline vector<Light*>* getLights() { return lights; };
	inline Color getBackground() { return background; };
	//TODO: replace getters by adders and deleters to remove direct access to private member
private: 
	vector<SceneObject*>* sceneObjects;
	vector<Light*>* lights;
	Color background;
};
