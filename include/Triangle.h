#pragma once
#include "Hitable.h"
#include <memory>
class Triangle : public Hitable
{

public:
	Triangle() = delete;
	Triangle(Vec3 vert0, Vec3 vert1, Vec3 vert2);
	bool hit(Ray r, float tMin, float tMax, HitRecord& rec);
	void setMaterial(std::shared_ptr<Material> m );





private:
	std::shared_ptr<Material> mat;
	Vec3 vertex0;
	Vec3 vertex1;
	Vec3 vertex2;








};

