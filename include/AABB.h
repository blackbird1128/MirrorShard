#pragma once
#include "vec3.h"
#include <algorithm>

class Triangle;
class Sphere;
class Ray;

class AABB 
{
public:
	AABB() = default;
	AABB(Vec3& maxP, Vec3& minP);
	AABB(Triangle tr);
	AABB(Sphere sp);
	bool hit(Ray r);
	void expand(AABB box );
	int longestAxis();

private:

	Vec3 pMax;
	Vec3 pMin;

};

