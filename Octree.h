#pragma once
#include <vector>
#include "SceneObject.h"
#include <iostream>

using namespace std;

// base on http://www.gamedev.net/page/resources/_/technical/game-programming/introduction-to-octrees-r3529

#define MIN_SIZE 0.1

class Node{
public:
	Node(Vec3 min, Vec3 max, vector<SceneObject*>* sceneObjects);
	~Node();

	void addChild(Node* child){ children->push_back(child); };
	void addSceneObject(SceneObject* sceneObject){ sceneObjects->push_back(sceneObject); };
	/**
	* recursive fonction for build the tree
	**/
	void buildTree();
	/**
	* Check if the scene object is in the region
	**/
	bool Contains(SceneObject*);
	/**
	* Determine the best scene objet collide
	* return : impact point and the best scene object collide
	* if not object was collide return ray's origin and nullptr
	**/
	pair<Vec3, SceneObject*> collide(Ray &ray);
	/**
	* Check if the ray intersect the region
	**/
	bool intersectRegion(Ray &ray);
private:
	Vec3 minim;
	Vec3 maxim;
	vector<Node*>* children;
	vector<SceneObject*>* sceneObjects;
};

class Octree{
public:
	Octree(vector<SceneObject*>* sceneObjects);
	~Octree();
	vector<SceneObject*>* copy(vector<SceneObject*>* sceneObjects);
	/**
	* Determine the best scene objet collide
	* return : impact point and the best scene object collide
	* if not object was collide return ray's origin and nullptr
	**/
	pair<Vec3, SceneObject*> collide(Ray &ray);
private:
	// root node represent the all space
	Node* root;
};