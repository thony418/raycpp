#pragma once
#include <vector>
#include "SceneObject.h"

using namespace std;

// base on http://www.gamedev.net/page/resources/_/technical/game-programming/introduction-to-octrees-r3529

#define MIN_SIZE 1

class Node{
public:
	Node(Vec3 position, int size, vector<SceneObject*>* sceneObjects);
	Node(Vec3 position, int size, Node* parent, vector<SceneObject*>* sceneObjects);

	void addChild(Node* child);
	void buildTree();
private:
	Vec3 position;
	int size;
	Node* parent;
	vector<Node*> children;
	vector<SceneObject*>* sceneObjects;
};

class Octree{
public:
	Octree(vector<SceneObject*>* sceneObjects);
private:
	// root node represent the all space
	Node* root;
};