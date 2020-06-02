#pragma once
#include <vector>
#include <memory>
#include "Hitable.h"
#include "AABB.h"



class BVHNode 
{

public:
	BVHNode();
	BVHNode build(const std::vector<HittablePtr>& wordPart, std::size_t depth ,int minNodeSize);
	bool hit(Ray r, float tMin, float tMax, HitRecord& rec );




private:
	std::unique_ptr<BVHNode> leftNode;
	std::unique_ptr<BVHNode> rightNode;
	std::vector<HittablePtr> object;
	AABB box;
	bool isRoot;


};