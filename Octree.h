#pragma once
#include <vector>
#include "SceneObject.h"
#include <iostream>

using namespace std;

// base on http://www.gamedev.net/page/resources/_/technical/game-programming/introduction-to-octrees-r3529

#define MIN_SIZE 0.1

class Node{
public:
	Node(Vec3 min, Vec3 max, Node* parent, vector<SceneObject*>* sceneObjects);
	~Node();

	void addChild(Node* child){ children->push_back(child); };
	void addSceneObject(SceneObject* sceneObject){ sceneObjects->push_back(sceneObject); };
	void buildTree();
	bool Contains(SceneObject*);
	void printNode();
private:
	Vec3 min;
	Vec3 max;
	Node* parent;
	vector<Node*>* children;
	vector<SceneObject*>* sceneObjects;
};

class Octree{
public:
	Octree(vector<SceneObject*>* sceneObjects);
	~Octree();
	vector<SceneObject*>* copy(vector<SceneObject*>* sceneObjects);
	void printOctree();
private:
	// root node represent the all space
	Node* root;
};