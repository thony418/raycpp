/**
* \author Marie DARRIGOL & Anthony LEONARD & Ophélie PELLOUX-PRAYER & Olivier SOLDANO
* \project Ray-Tracing
* \file Scene.cpp
* \brief Constructors for the Scene class (empty or with some SceneObjects, some Lights and a background Color)
*/
#include "Scene.h"

Scene::Scene(){
	sceneObjects = new vector<SceneObject*>();
	lights = new vector<Light*>();
	background = Color(20, 20, 20);
}

Scene::Scene(vector<SceneObject*>* sceneObjects, vector<Light*>* lights, Color background) : 
	sceneObjects(sceneObjects), lights(lights), background(background){
}


