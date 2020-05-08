#pragma once
#include "vec3.h"
class AABB
{
public:
	AABB(Vec3 maxP, Vec3 minP);



private:

	Vec3 pMax;
	Vec3 pMin;



};

