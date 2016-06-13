#pragma once
#include "Position.h"
#include "Material.h"

class SceneObject{
	Position getPosition(){ return position; }
private:
	Position position;
	Material material;
};