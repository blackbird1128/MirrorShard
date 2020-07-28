#pragma once
#include "vec3.h"
#include "Ray.h"
#include "Material.h"
#include "Texture.h"
#include <memory>
#include <AABB.h>

class Material;
class AABB;

class HitRecord
{
public:
	float t =0;
	float normalisedDistInMat = 0;
	Vec3 p = {};
	Vec3 normal = {};
	std::shared_ptr<Material> mat;
	float u, v;
};



class Hittable
{
public:
	virtual bool hit(Ray r, float tMin, float tMax, HitRecord& rec) = 0;
	virtual AABB getAABB() = 0;
	virtual Vec3 getCenter() = 0;
	virtual float pdf(Vec3& origin, Vec3& direction) { return 0; }
	virtual Vec3 samplePoint(Vec3& origin) { return Vec3(0, 0, 0); }
};
using HittablePtr = std::shared_ptr<Hittable>;
