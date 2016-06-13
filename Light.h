#pragma once
#include "Position.h"

class Light{
public:
	Position getPosition(){ return position; };
private:
	Position position;
};