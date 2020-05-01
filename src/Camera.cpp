#include "Camera.h"
#include <cmath>
Camera::Camera(Vec3 lookfrom , Vec3 lookat , Vec3 vup ,float vfov , float aspect)
{
	Vec3 u, v, w;
	float theta = vfov * 3.14159265359 / 180;
	float halfHeight = tan(theta / 2);
	float halfWidth = aspect * halfHeight;
	lowerLeftCorner = Vec3(-halfWidth , -halfHeight , -1.0);
	horizontal = Vec3(2*halfWidth ,0.0,0.0);
	vertical = Vec3(0.0, 2.0*halfHeight, 0.0);
	origin = Vec3(0.0, 0.0, 0.0);
}

Ray Camera::getRay(float u, float v)
{
	return Ray(origin, lowerLeftCorner + u * horizontal + v * vertical - origin);
}
