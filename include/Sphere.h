#pragma once
#include "Hitable.h"
#include "vec3.h"
#include "Material.h"
#include <memory>

class AABB;


class Sphere : public Hittable
{
public:
	Sphere() = default;
	Sphere(Vec3 center, float radius);
	void setMaterial(std::shared_ptr<Material> m);
	bool hit(Ray r, float tMin, float tMax, HitRecord& rec );
    float pdf(Vec3& origin, Vec3& direction) override;
	Vec3 samplePoint(Vec3& origin) override;
	AABB getAABB();
	Vec3 getCenter();
	float getRadius();

private:
	Vec3 center;
	float radius;
	std::shared_ptr<Material> mat;

};

