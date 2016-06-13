#include "Collider.h"

pair<Position, SceneObject*> Collider::collide(Ray &ray, vector<SceneObject*>* sceneObjects){
	// init the best impact point to the ray position
	Position best_impact_point = ray.getOrigin();
	// get the origin of the ray
	Position ray_origin = ray.getOrigin();
	// declare the best scene object;
	SceneObject* best_sceneObject = nullptr;
	// declare the best distance
	float best_dist = 0.0;
	// declare the current distance
	float dist = 0.0;
	// declare the pair for the intersect function
	pair<bool, Position> pair_intersect;
	//for each object of the scene
	for (vector<SceneObject*>::iterator it = sceneObjects->begin(); it != sceneObjects->end(); it++){
		// determine if the ray intersect the object
		pair_intersect = (*it)->intersect(ray);
		if (pair_intersect.first){
			// calcul the distance between the ray and the impact point
			dist = ray_origin.dist(pair_intersect.second);
			// if it's the best
			if (best_dist > dist){
				best_dist = dist;
				best_sceneObject = *it;
				best_impact_point = pair_intersect.second;
			}
		}
	}
	return pair<Position, SceneObject*>(best_impact_point, best_sceneObject);
}

pair<Position, SceneObject*> Collider::collide(Ray &ray, Scene &scene){
	// get the vector of scene object of the scene
	vector<SceneObject*>* sceneObjects = scene.getSceneObjects();
	return collide(ray, sceneObjects);
}