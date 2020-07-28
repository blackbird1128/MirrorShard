#pragma once
#include "Hitable.h"
#include "Ray.h"
#include "Model.h"
#include "Camera.h"
#include "Image.h"
#include "BVHNode.h"
#include <vector>
#include <random>
#include <memory>
class Scene
{
public:

	Scene(Camera& sceneCamera, std::vector<HittablePtr> objToSample) : cam(sceneCamera), BVHinitialized(false) { sampledObjects = objToSample; };
	Color color(Ray& r, BVHNode& tree, int depth);
	void render(std::string filepath, int height, int width , int rayPerPixel);
	bool hit(Ray r, float tMin, float tMax, HitRecord& rec);
	void buildBVH();
	void addObject(const HittablePtr object);
	void addObject(const Model& model);
	
private:



	Camera cam;
	BVHNode sceneTree;
	bool BVHinitialized;
	std::vector<HittablePtr> Objects;
	std::vector<HittablePtr> sampledObjects;

};

