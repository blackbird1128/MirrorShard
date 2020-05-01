#pragma once
#include "Hitable.h"
#include "vec3.h"
#include "Material.h"
#include <memory>
class Sphere: public Hitable
{
public:
	Sphere() = default;
	Sphere(Vec3 center, float radius);
	void setMaterial(std::shared_ptr<Material> m);
	bool hit(Ray r, float tMin, float tMax, HitRecord& rec );

private:
	Vec3 center;
	float radius;
	std::shared_ptr<Material> mat;

};

