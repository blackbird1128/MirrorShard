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
	void addObject(std::unique_ptr<Hitable> obj);
	void addObject(std::unique_ptr<Model> model);
private:
	std::vector<std::unique_ptr<Hitable>> Objects;



};

