#pragma once
#include <random>
#include "vec3.h"

//ugly and need to be refactored 
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


	static Vec3 randomUnitVector() {
		std::uniform_real_distribution<> disA(0, 2 * 3.14159265359);
		auto a = disA(gen);
		std::uniform_real_distribution<> disZ(-1, 1);
		auto z = disZ(gen);
		auto r = std::sqrtf(1.0 - z * z);
		return Vec3(r * cos(a), r * sin(a), z);
	}


	static Vec3 randomCosineDirection() {
		auto r1 = quickRandom();
		auto r2 = quickRandom();
		auto z = sqrt(1 - r2);

		auto phi = 2 * 3.14159265359 * r1;
		auto x = cos(phi) * sqrt(r2);
		auto y = sin(phi) * sqrt(r2);

		return Vec3(x, y, z);
	}


	static float quickRandom()
	{
		return dis(gen);

	}

	static Vec3 randomToSphere(double radius, double distanceSquared)
	{
		auto r1 = dis(gen);
		auto r2 = dis(gen);
		auto z = 1 + r2 * (sqrt(1 - radius * radius / distanceSquared) - 1);

		auto phi = 2 * 3.14159265359 * r1;
		auto x = cos(phi) * sqrt(1 - z * z);
		auto y = sin(phi) * sqrt(1 - z * z);

		return Vec3(x, y, z);
	
	}

	static int randomInt(int start, int end)
	{
	
		std::uniform_int_distribution<> disInt(start, end);
		return disInt(gen);
	
	}

};