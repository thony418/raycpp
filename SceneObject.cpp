#include "SceneObject.h"

SceneObject::SceneObject() : position(Vec3()), material(Material()){
}

SceneObject::SceneObject(Vec3 & position, Material & material) : position(position), material(material){
}
