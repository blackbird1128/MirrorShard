#pragma once
#include <random>
#include "vec3.h"


namespace
{
	Vec3 p;
	std::random_device dev;
	std::mt19937 gen(dev());
	std::uniform_real_distribution<> dis(0.0, 1.0);
}

class utils
{

public:
	static Vec3 randomInUnitSphere()
	{


		float u1 = dis(gen);
		float u2 = dis(gen);
		float lat = acos(2 * u1 - 1) - (3.14159265359 / 2);
		float longitude = 3.14159265359 * 2 * u2;
		float coslat = cos(lat);
		p.x = coslat * cos(longitude);
		p.y = coslat * sin(longitude);
		p.z = sin(lat);
		return p;


	}



	static float quickRandom()
	{
		return dis(gen);

	}


};