#include "Scene.h"
#include "Sphere.h"
#include "Hitable.h"


bool Scene::hit(Ray r, float tMin, float tMax, HitRecord& rec)
{

	bool hitAnything = false;
	double closestSoFar = tMax;
	HitRecord tempRec;
	for (int i = 0; i < Objects.size(); i++)
	{
	
		if (Objects[i]->hit(r, tMin, closestSoFar, tempRec))
		{
			hitAnything = true;
			closestSoFar = tempRec.t;
			rec = std::move(tempRec);
		}
	}
	return hitAnything;


}

void Scene::addObject(std::unique_ptr<Hitable> obj)
{
	Objects.push_back(std::move(obj));
}
