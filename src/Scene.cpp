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
			rec = tempRec;
		}
	}
	return hitAnything;


}

void Scene::addObject(const HittablePtr object)
{
	Objects.push_back(object);
}

void Scene::addObject(const Model& model)
{
	for (int i = 0; i < model.triangles.size(); i++)
	{
		Objects.push_back(std::make_shared<Triangle>(model.triangles[i]));

	}


}