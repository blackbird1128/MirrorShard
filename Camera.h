#pragma once
#include "vec3.h"
#include "Ray.h"
class Camera
{
public:
	Camera(Vec3 lookfrom, Vec3 lookat, Vec3 vup, float vfov, float aspect);
	Ray getRay(float u, float v);




	Vec3 origin;
	Vec3 lowerLeftCorner;
	Vec3 horizontal;
	Vec3 vertical;





};

