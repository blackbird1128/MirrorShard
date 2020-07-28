#include "ONB.h"
#include "..\include\ONB.h"

Vec3 ONB::u()
{
	return xAxis;
}

Vec3 ONB::v()
{
	return yAxis;
}

Vec3 ONB::w()
{
	return zAxis;
}

Vec3 ONB::local(float a, float b, float c)
{
	return a * xAxis + b * yAxis + c * zAxis;
}

Vec3 ONB::local(Vec3& a)
{
	return a.x * xAxis + a.y * yAxis + a.z * zAxis;
}

void ONB::buildFromW(Vec3& wVec)
{
	zAxis = unitVector(wVec);
	Vec3 a  = (fabs(zAxis.x) > 0.9) ? Vec3(0, 1, 0) : Vec3(1, 0, 0);
	yAxis = unitVector(zAxis.crossProduct(a));
	xAxis = zAxis.crossProduct(yAxis);
}
