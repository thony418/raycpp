/**
* \author Marie DARRIGOL & Anthony LEONARD & Ophélie PELLOUX-PRAYER & Olivier SOLDANO
* \project Ray-Tracing
* \file SceneObject.cpp
* \brief Constructors for the SceneObject class (empty or with a position and a Material)
*/
#include "SceneObject.h"

SceneObject::SceneObject() : position(Vec3()), material(Material()){
}

SceneObject::SceneObject(Vec3 & position, Material & material) : position(position), material(material){
}
