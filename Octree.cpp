#include "Octree.h"
#include <algorithm>

/**
 * Constructor
**/
Node::Node() : minim(Vec3()), maxim(Vec3()) {
	children = new vector<Node*>();
	sceneObjects = new vector<SceneObject*>();
}


Node::Node(Vec3 min, Vec3 max, vector<SceneObject*>* sceneObjects){
	this->minim = min;
	this->maxim = max;
	this->children = new vector<Node*>();
	this->sceneObjects = sceneObjects;
}

Node::~Node(){
	for (vector<SceneObject*>::iterator it = sceneObjects->begin(); it != sceneObjects->end(); it++){
		delete (*it);
	}
	delete sceneObjects;
	for (vector<Node*>::iterator child = children->begin(); child != children->end(); child++){
		delete (*child);
	}
	delete children;
}

Octree::Octree() {
	root = new Node();
}

Octree::Octree(vector<SceneObject*>* sceneObjects){
	vector<SceneObject*>* my_sceneObjects = copy(sceneObjects);
	// declare min whit infinit float
	Vec3 min = Vec3(numeric_limits<float>::infinity(), numeric_limits<float>::infinity(), numeric_limits<float>::infinity());
	// declare max
	Vec3 max = Vec3(0,0,0);
	Vec3 min_tmp = min;
	Vec3 max_tmp = max;
	// find the min and max coordonate
	for (vector<SceneObject*>::iterator it = my_sceneObjects->begin(); it != my_sceneObjects->end(); it++){
		min_tmp = (*it)->minCoordinates();
		if (min_tmp.getX() < min.getX()){
			min.setX(min_tmp.getX());
		}
		if (min_tmp.getY() < min.getY()){
			min.setY(min_tmp.getY());
		}
		if (min_tmp.getZ() < min.getZ()){
			min.setZ(min_tmp.getZ());
		}

		max_tmp = (*it)->maxCoordinates();
		if (max_tmp.getX() > max.getX()){
			max.setX(max_tmp.getX());
		}
		if (max_tmp.getY() > max.getY()){
			max.setY(max_tmp.getY());
		}
		if (max_tmp.getZ() > max.getZ()){
			max.setZ(max_tmp.getZ());
		}
	}
	// associate the root
	root = new Node(min, max, my_sceneObjects);
	root->buildTree();
}

Octree::~Octree(){
	delete root;
}

vector<SceneObject*>* Octree::copy(vector<SceneObject*>* sceneObjects){
	vector<SceneObject*>* copy = new vector<SceneObject*>();
	for (vector<SceneObject*>::iterator it = sceneObjects->begin(); it != sceneObjects->end(); it++){
		copy->push_back((*it));
	}
	return copy;
}

pair<Vec3, SceneObject*> Octree::collide(Ray &ray){
	return root->collide(ray);
}

void Node::buildTree(){
	//  verif if the sceneObjects contains more of one object
	if ((int) sceneObjects->size() <= 1){
		return;
	}

	// calculate the dimensions of the region
	Vec3 dimension = maxim - minim;

	// determinate if the region's dimension are greater than the minimal dimensions
	if (dimension.getX() <= MIN_SIZE && dimension.getY() <= MIN_SIZE && dimension.getZ() <= MIN_SIZE){
		return;
	}

	Vec3 half = dimension / 2;
	Vec3 center = minim + half;

	// construct the children and add to the parent list
	Node* childSW = new Node(minim, center, new vector<SceneObject*>());
	addChild(childSW);
	Node* childSE = new Node(Vec3(center.getX(), minim.getY(), minim.getZ()), Vec3(maxim.getX(), center.getY(), center.getZ()), new vector<SceneObject*>());
	addChild(childSE);
	Node* childSED = new Node(Vec3(center.getX(), minim.getY(), center.getZ()), Vec3(maxim.getX(), center.getY(), maxim.getZ()), new vector<SceneObject*>());
	addChild(childSED);
	Node* childSWD = new Node(Vec3(minim.getX(), minim.getY(), center.getZ()), Vec3(center.getX(), center.getY(), maxim.getZ()), new vector<SceneObject*>());
	addChild(childSWD);
	Node* childNW = new Node(Vec3(minim.getX(), center.getY(), minim.getZ()), Vec3(center.getX(), maxim.getY(), center.getZ()), new vector<SceneObject*>());
	addChild(childNW);
	Node* childNE = new Node(Vec3(center.getX(), center.getY(), minim.getZ()), Vec3(maxim.getX(), maxim.getY(), center.getZ()), new vector<SceneObject*>());
	addChild(childNE);
	Node* childNED = new Node(center, maxim, new vector<SceneObject*>());
	addChild(childNED);
	Node* childNWD = new Node(Vec3(minim.getX(), center.getY(), center.getZ()), Vec3(center.getX(), maxim.getY(), maxim.getZ()), new vector<SceneObject*>());
	addChild(childNWD);

	// contains all of the objects which got moved down the tree and can be erase from this node.
	vector<vector<SceneObject*>::iterator>* devec = new vector<vector<SceneObject*>::iterator>();

	for (vector<SceneObject*>::iterator it = sceneObjects->begin(); it != sceneObjects->end(); it++){
		//if ((*it)->minCoordinates() != (*it)->maxCoordinates()){} // TODO : check if the object have a size (for the sphere if the radius != 0)
		for (vector<Node*>::iterator child = children->begin(); child != children->end(); child++){
			if ((*child)->Contains((*it))){
				(*child)->addSceneObject((*it));
				devec->push_back(it);
				break;
			}
		}
	}

	for (int i = devec->size() - 1; i >= 0; i--){
		sceneObjects->erase(devec->at(i));
	}

	for (vector<Node*>::iterator child = children->begin(); child != children->end(); child++){
		(*child)->buildTree();
	}
}

bool Node::Contains(SceneObject* sceneObject){
	return sceneObject->minCoordinates().getX() >= minim.getX()
		&& sceneObject->minCoordinates().getY() >= minim.getY()
		&& sceneObject->minCoordinates().getZ() >= minim.getZ()
		&& sceneObject->maxCoordinates().getX() <= maxim.getX()
		&& sceneObject->maxCoordinates().getY() <= maxim.getY()
		&& sceneObject->maxCoordinates().getZ() <= maxim.getZ();
}

pair<Vec3, SceneObject*> Node::collide(Ray &ray){
	// if no more child and no more sceneObject return null for close the recursion
	if ((int)sceneObjects->size() == 0 && (int) children->size() == 0){
		return pair<Vec3, SceneObject*>(Vec3(0, 0, 0), nullptr);
	}
	// init the best impact point to the ray position
	Vec3 best_impact_point = ray.getOrigin();
	// init the best impact point to the ray position
	Vec3 best_impact_point_child = ray.getOrigin();
	// declare the best scene object;
	SceneObject* best_sceneObject = nullptr;
	// declare the best scene object;
	SceneObject* best_sceneObject_child = nullptr;
	// declare the best distance
	float best_dist = numeric_limits<float>::infinity();
	// declare the current distance
	float dist = 0.0;
	// declare the pair for the intersect function
	pair<bool, Vec3> pair_intersect;
	// declare impact point
	Vec3 impact_point;

	for (vector<SceneObject*>::iterator obj = sceneObjects->begin(); obj != sceneObjects->end(); obj++){
		// determine if the ray intersect the object
		pair_intersect = (*obj)->intersect(ray);
		if (pair_intersect.first){
			// compute the distance between the ray and the impact point
			impact_point = pair_intersect.second - ray.getOrigin();
			dist = impact_point.length();
			// if it's the best
			if (best_dist > dist){
				best_dist = dist;
				best_sceneObject = *obj;
				best_impact_point = pair_intersect.second;
			}
		}
	}
	// check the collide with the children
	pair<Vec3, SceneObject*> pair_collide;
	for (vector<Node*>::iterator child = children->begin(); child != children->end(); child++){
		if ((*child)->intersectRegion(ray)){
			pair_collide = (*child)->collide(ray);
			if (pair_collide.second != nullptr){
				best_sceneObject_child = pair_collide.second;
				best_impact_point_child = pair_collide.first;
				break;
			}
		}
	}

	// if we find an objet it's the best of the branch
	if (best_sceneObject != nullptr){
		if (best_sceneObject_child != nullptr){
			impact_point = best_impact_point_child - ray.getOrigin();
			dist = impact_point.length();
			// if it's the best
			if (best_dist > dist){
				return pair<Vec3, SceneObject*>(best_impact_point_child, best_sceneObject_child);
			}
			else{
				return pair<Vec3, SceneObject*>(best_impact_point, best_sceneObject);
			}
		}
		else{
			return pair<Vec3, SceneObject*>(best_impact_point, best_sceneObject);
		}		
	}

	return pair<Vec3, SceneObject*>(best_impact_point, best_sceneObject);
}

bool Node::intersectRegion(Ray &ray){
	float tmin = (minim.getX() - ray.getOrigin().getX()) / ray.getDirection().getX();
	float tmax = (maxim.getX() - ray.getOrigin().getX()) / ray.getDirection().getX();

	if (tmin > tmax) swap(tmin, tmax);

	float tymin = (minim.getY() - ray.getOrigin().getY()) / ray.getDirection().getY();
	float tymax = (maxim.getY() - ray.getOrigin().getY()) / ray.getDirection().getY();

	if (tymin > tymax) swap(tymin, tymax);

	if ((tmin > tymax) || (tymin > tmax))
		return false;

	tmin = min(tymin, tmin);
	tmax = min(tymax, tmax);

	float tzmin = (minim.getZ() - ray.getOrigin().getZ()) / ray.getDirection().getZ();
	float tzmax = (maxim.getZ() - ray.getOrigin().getZ()) / ray.getDirection().getZ();

	if (tzmin > tzmax) swap(tzmin, tzmax);

	if ((tmin > tzmax) || (tzmin > tmax))
		return false;

	tmin = min(tzmin, tmin);
	tmax = min(tzmax, tmax);

	return true;
}