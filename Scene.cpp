#include "Scene.h"

Scene::Scene(){
	sceneObjects = new vector<SceneObject*>();
	lights = new vector<Light*>();
}

Scene::Scene(vector<SceneObject*>* sceneObjects, vector<Light*>* lights, Color background) : 
	sceneObjects(sceneObjects), lights(lights), background(background){
}


