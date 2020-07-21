#pragma once
#include "Color.h"
#include "vec3.h"
class Texture
{
public:
	virtual Color getColor(double u, double v) = 0;
	int u, v;
};

