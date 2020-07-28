#pragma once
#include "vec3.h"
class ONB
{
public:
	ONB() = default;
	Vec3 u();
	Vec3 v();
	Vec3 w();

	Vec3 local(float a, float b, float c);
	Vec3 local(Vec3& a);


	void buildFromW(Vec3& w);
private:
	Vec3 xAxis;
	Vec3 yAxis;
	Vec3 zAxis;


};

