#pragma once
#include "vec3.h"
class Ray
{
public:
	Ray() = default;
	Ray(const Vec3& a, const Vec3& b); 
	const Vec3& origin();
	const Vec3& direction();
	Vec3 pointAt(float t);
private:

	Vec3 A;
	Vec3 B;




};

