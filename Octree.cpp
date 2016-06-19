#include "Octree.h"

/**
 * Constructor
**/

Node::Node(Vec3 position, int size, vector<SceneObject*>* sceneObjects){
	this->position = position;
	this->size = size;
	this->parent = nullptr;
	this->children = vector<Node*>();
	this->sceneObjects = sceneObjects;
}

Node::Node(Vec3 position, int size, Node* parent, vector<SceneObject*>* sceneObjects){
	this->position = position;
	this->size = size;
	this->parent = parent;
	this->children = vector<Node*>();
	this->sceneObjects = sceneObjects;
}

Octree::Octree(vector<SceneObject*>* sceneObjects){
	// declare min whit infinit float
	Vec3 min = Vec3(numeric_limits<float>::infinity(), numeric_limits<float>::infinity(), numeric_limits<float>::infinity());
	// declare max
	Vec3 max = Vec3(0,0,0);
	Vec3 min_tmp = min;
	Vec3 max_tmp = max;
	// find the min and max coordonate
	for (vector<SceneObject*>::iterator it = sceneObjects->begin(); it != sceneObjects->end(); it++){
		min_tmp = (*it)->minCoordinates();
		if (min_tmp.getX() < min.getX()){
			min.setX(min_tmp.getX());
		}
		if (min_tmp.getY() < min.getY()){
			min.setX(min_tmp.getY());
		}
		if (min_tmp.getZ() < min.getZ()){
			min.setX(min_tmp.getZ());
		}

		max_tmp = (*it)->maxCoordinates();
		if (max_tmp.getX() > max.getX()){
			max.setX(max_tmp.getX());
		}
		if (max_tmp.getY() > max.getY()){
			max.setX(max_tmp.getY());
		}
		if (max_tmp.getZ() > max.getZ()){
			max.setX(max_tmp.getZ());
		}
	}
	// calcul the center of the box root
	Vec3 position = (min + max) / 2;
	// calcul box size
	int size = (int) (max.getX() - position.getX()); // TODO : test with Y or Z
	// associate the root
	root = new Node(position, size, sceneObjects);
	root->buildTree();
}

void Node::buildTree(){

}