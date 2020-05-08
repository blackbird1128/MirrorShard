#include "Camera.h"
#include <cmath>
Camera::Camera(Vec3 lookfrom , Vec3 lookat , Vec3 vup ,float vfov , float aspect)
{
	Vec3 u, v, w;
	float theta = vfov * 3.14159265359 / 180;
	float halfHeight = tan(theta / 2);
	float halfWidth = aspect * halfHeight;
	origin = lookfrom;
	w = unitVector(lookfrom - lookat);
	u = unitVector(vup.crossProduct(w));
	v = w.crossProduct(u);
	lowerLeftCorner = Vec3(-halfWidth, -halfHeight, -1.0);
	lowerLeftCorner = origin - halfWidth * u - halfHeight * v - w;
	horizontal = 2 * halfWidth * u;
	vertical = 2 * halfHeight * v;
}

Ray Camera::getRay(float u, float v)
{
	return Ray(origin, lowerLeftCorner + u * horizontal + v * vertical - origin);
}
