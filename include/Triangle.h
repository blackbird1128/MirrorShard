#pragma once
#include "Hitable.h"
#include <memory>
class Triangle : public Hitable
{

public:
	Triangle() = default;
	Triangle(Vec3 vert0, Vec3 vert1, Vec3 vert2);
	bool hit(Ray r, float tMin, float tMax, HitRecord& rec);
	void setMaterial(std::shared_ptr<Material> m );
	void computeEdges();

	Vec3 vertex0;
	Vec3 vertex1;
	Vec3 vertex2;
	
	Vec3 vertex0Normal;
	Vec3 vertex1Normal;
	Vec3 vertex2Normal;

	Vec3 edge1;
	Vec3 edge2;
private:
	std::shared_ptr<Material> mat;









};

