/**
* \author Marie DARRIGOL & Anthony LEONARD & Ophélie PELLOUX-PRAYER & Olivier SOLDANO
* \project Ray-Tracing
* \file scene.h
* \brief represent a scene, containing the objects to draw, the lights, and the background color.
*/

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
	vector<SceneObject*>* sceneObjects; ///< objects to be drawn
	vector<Light*>* lights; ///< lights on the scene
	Color background; ///< background color of the scene
};
