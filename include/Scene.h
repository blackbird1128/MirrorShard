#pragma once
#include "Hitable.h"
#include "Ray.h"
#include "Model.h"
#include <vector>
#include <memory>
class Scene
{
public:

	bool hit(Ray r, float tMin, float tMax, HitRecord& rec);
	void addObject(const HittablePtr object);
	void addObject(const Model& model);
	std::vector<HittablePtr> Objects;
private:
	



};

