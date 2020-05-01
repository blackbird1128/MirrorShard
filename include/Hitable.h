#pragma once
#include "vec3.h"
#include "Ray.h"
#include "Material.h"
#include <memory>
class Material;

class HitRecord
{
public:
	float t =0;
	float normalisedDistInMat = 0;
	Vec3 p = {};
	Vec3 normal = {};
	std::shared_ptr<Material> mat;
};

class Hitable
{
public:
	virtual bool hit(Ray r, float tMin, float tMax, HitRecord& rec) = 0;
};

