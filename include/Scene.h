#pragma once
#include "Hitable.h"
#include "Ray.h"
#include "Model.h"
#include "Camera.h"
#include "Image.h"
#include "BVHNode.h"
#include "hittablePdf.h"
#include <vector>
#include <random>
#include <memory>
class Scene
{
public:

	Scene(Camera& sceneCamera, std::vector<HittablePtr> objToSample ,int maxDepth = 10) : cam(sceneCamera), BVHinitialized(false)
	{
		for (int i = 0; i < objToSample.size(); i++)
		{
			sampledPdf.push_back(hittablePdf(std::move(objToSample[i]), Vec3(0, 0, 0)));
		}
		maxDepthParameter = maxDepth;
	};
	Color color(Ray& r, BVHNode& tree, int depth);
	void render(std::string filepath, int height, int width , int rayPerPixel);
	Image renderArea(int xStart, int xStop, int YStart, int YStop);
	Vec3 Uncharted2Tonemap(Vec3 x);
	bool hit(Ray r, float tMin, float tMax, HitRecord& rec);
	void buildBVH();
	void addObject(const HittablePtr object);
	void addObject(const Model& model);
	
private:



	Camera cam;
	BVHNode sceneTree;
	bool BVHinitialized;
	std::vector<HittablePtr> Objects;
	std::vector<hittablePdf> sampledPdf;
	int maxDepthParameter;
};

