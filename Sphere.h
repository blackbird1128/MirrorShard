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
	void setMat(std::shared_ptr<Material> m);
	virtual bool hit(Ray r, float tMin, float tMax, HitRecord& rec );

private:
	Vec3 center;
	float radius;
	std::shared_ptr<Material> mat;

};

