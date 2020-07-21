#pragma once
#include "Hitable.h"
#include <AABB.h>
#include <memory>




class Triangle : public Hittable
{

public:
	Triangle() = default;
	Triangle(Vec3 vert0, Vec3 vert1, Vec3 vert2);
	bool hit(Ray r, float tMin, float tMax, HitRecord& rec);
	void setMaterial(std::shared_ptr<Material> m );
	void computeEdges();
	AABB getAABB();
	Vec3 getCenter();

	Vec3 vertex0;
	Vec3 vertex1;
	Vec3 vertex2;
	
	Vec3 vertex0Normal;
	Vec3 vertex1Normal;
	Vec3 vertex2Normal;

	Vec3 edge1;
	Vec3 edge2;

	Vec3 vertex0uv; // use 3d vector for 2d coordinates need to be changed 
	Vec3 vertex1uv;
	Vec3 vertex2uv;
private:
	std::shared_ptr<Material> mat;

};

bool operator==(Triangle t1, Triangle t2);
