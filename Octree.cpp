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
	for (vector<SceneObject*>::iterator it = sceneObjects->begin(); it != sceneObjects->end(); it++){
		
	}
}