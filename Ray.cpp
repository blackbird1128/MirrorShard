#include "Ray.h"

const Vec3& Ray::origin()
{
	return A;
}

const Vec3& Ray::direction()
{
	return B;
}

Vec3 Ray::pointAt(float t)
{
	return A + t*B;
}

Ray::Ray(const Vec3& a, const Vec3& b)
{
	A = a, B = b ;
}
