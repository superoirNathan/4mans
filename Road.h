#pragma once

#include "GameObject.h"
#include <fstream>

class Road : public GameObject
{

public:
	Road();
	Road(Mesh &m);
	~Road();

};
