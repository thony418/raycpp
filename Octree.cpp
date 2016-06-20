#include "Octree.h"

/**
 * Constructor
**/
Node::Node(Vec3 min, Vec3 max, Node* parent, vector<SceneObject*>* sceneObjects){
	this->min = min;
	this->max = max;
	this->parent = parent;
	this->children = new vector<Node*>();
	this->sceneObjects = sceneObjects;
}

Node::~Node(){
	for (vector<SceneObject*>::iterator obj = sceneObjects->begin(); obj != sceneObjects->end(); obj++){
		delete (*obj);
	}
	for (vector<Node*>::iterator child = children->begin(); child != children->end(); child++){
		delete (*child);
	}
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
	root = new Node(min, max, nullptr, my_sceneObjects);
	root->buildTree();

	printOctree();
}

Octree::~Octree(){
	delete root;
}

void Octree::printOctree(){
	root->printNode();
}

vector<SceneObject*>* Octree::copy(vector<SceneObject*>* sceneObjects){
	vector<SceneObject*>* copy = new vector<SceneObject*>();
	for (vector<SceneObject*>::iterator it = sceneObjects->begin(); it != sceneObjects->end(); it++){
		copy->push_back((*it));
	}
	return copy;
}

void Node::buildTree(){
	//  verif if the sceneObjects contains more of one object
	if ((int) sceneObjects->size() <= 1){
		return;
	}

	// calculate the dimensions of the region
	Vec3 dimension = max - min;

	// determinate if the region's dimension are greater than the minimal dimensions
	if (dimension.getX() <= MIN_SIZE && dimension.getY() <= MIN_SIZE && dimension.getZ() <= MIN_SIZE){
		return;
	}

	Vec3 half = dimension / 2;
	Vec3 center = min + half;

	// construct the children and add to the parent list
	Node* childSW = new Node(min, center, this, new vector<SceneObject*>());
	addChild(childSW);
	Node* childSE = new Node(Vec3(center.getX(), min.getY(), min.getZ()), Vec3(max.getX(), center.getY(), center.getZ()), this, new vector<SceneObject*>());
	addChild(childSE);
	Node* childSED = new Node(Vec3(center.getX(), min.getY(), center.getZ()), Vec3(max.getX(), center.getY(), max.getZ()), this, new vector<SceneObject*>());
	addChild(childSED);
	Node* childSWD = new Node(Vec3(min.getX(), min.getY(), center.getZ()), Vec3(center.getX(), center.getY(), max.getZ()), this, new vector<SceneObject*>());
	addChild(childSWD);
	Node* childNW = new Node(Vec3(min.getX(), center.getY(), min.getZ()), Vec3(center.getX(), max.getY(), center.getZ()), this, new vector<SceneObject*>());
	addChild(childNW);
	Node* childNE = new Node(Vec3(center.getX(), center.getY(), min.getZ()), Vec3(max.getX(), max.getY(), center.getZ()), this, new vector<SceneObject*>());
	addChild(childNE);
	Node* childNED = new Node(center, max, this, new vector<SceneObject*>());
	addChild(childNED);
	Node* childNWD = new Node(Vec3(min.getX(), center.getY(), center.getZ()), Vec3(center.getX(), max.getY(), max.getZ()), this, new vector<SceneObject*>());
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
	return sceneObject->minCoordinates().getX() >= min.getX()
		&& sceneObject->minCoordinates().getY() >= min.getY()
		&& sceneObject->minCoordinates().getZ() >= min.getZ()
		&& sceneObject->maxCoordinates().getX() <= max.getX()
		&& sceneObject->maxCoordinates().getY() <= max.getY()
		&& sceneObject->maxCoordinates().getZ() <= max.getZ();
}

void Node::printNode(){
	if ((int)sceneObjects->size() > 0){
		cout << "[";
		for (vector<SceneObject*>::iterator obj = sceneObjects->begin(); obj != sceneObjects->end(); obj++){
			(*obj)->printSceneObject();
			cout << ", ";
		}
		cout << "]" << endl;
	}
	if ((int)children->size() > 0){
		for (vector<Node*>::iterator child = children->begin(); child != children->end(); child++){
			(*child)->printNode();
		}
	}
}