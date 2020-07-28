#pragma once
#include "vec3.h"
class pdf
{
public:

	virtual float value(Vec3& direction) = 0;
	virtual Vec3 generate() = 0;

};

