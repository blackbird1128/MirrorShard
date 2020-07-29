#include "Scene.h"
#include "Sphere.h"
#include "Hitable.h"
#include "cosinePdf.h"
#include "hittablePdf.h"
#include "MixturePdf.h"
#include "MathUtils.hpp"
Color Scene::color(Ray& r, BVHNode& tree, int depth)
{

	/*
	if (tree.hit(r, 0.001, std::numeric_limits<float>::max(), rec))
	{ 

		Ray scattered;
		Color attenuation;
		if (depth < 5 && rec.mat->scatter(r, rec, attenuation, scattered))
		{
			return attenuation * color(scattered, tree, depth + 1);
		}
		else
		{
			return Color(0, 0, 0);
		}
	}
	else
	{
		Vec3 unitDirection = unitVector(r.direction());
		float t = 0.5 * (unitDirection.y + 1.0);
		return (1.0 - t) * Color(1.0, 1.0, 1.0) + t * Color(0.5, 0.7, 1.0);
	}
	*/

	/*
	if (depth > 3)
	{
		return Color(0, 0, 0);
	}

	if (!tree.hit(r, 0.001, std::numeric_limits<float>::max(), rec))
		return Color(0,0,0);

	Ray scattered;
	Color attenuation;
	Color emitted = rec.mat->getEmissive();

	if (!rec.mat->scatter(r, rec, attenuation, scattered))
		return emitted;

	return emitted + attenuation * color(scattered, tree, depth +1);
	*/




	

	HitRecord rec;
	if (depth > 3)
	{
		return Color(0, 0, 0);
	}
	if (!tree.hit(r, 0.001, std::numeric_limits<float>::max(), rec))
	{
		return (Color(0, 0, 0));
	}


	Ray scattered;
	float pdf = 0;
	Color emitted = rec.mat->getEmissive();
	scatterRecord scatterRec;
	if (!rec.mat->scatter(r, rec, scatterRec, scattered))
	{
		return emitted;
	}
	if (rec.mat->isSpecular())
	{

		return scatterRec.attenuation * color(scatterRec.specular_ray, tree, depth + 1);
	}
	
	std::vector<pdfPtr> actualPdf;
	for (int i = 0 ; i < sampledPdf.size();i++)
	{
		sampledPdf[i].setOrigin(rec.p);
		pdfPtr temp = std::make_unique<hittablePdf>( sampledPdf[i]);
		actualPdf.push_back(std::move(temp));
	}
	


	MixturePdf hittableMix(std::move(actualPdf));
	//std::vector<pdfPtr> secondMixVec;;
	//secondMixVec.push_back(std::move(scatterRec.pdfPointer));
//	secondMixVec.push_back(std::move(std::make_unique<pdfPtr>(hittableMix)));
	//MixturePdf finalMix(std::move(secondMixVec));


	Vec3 pdfDirection;
	if (utils::quickRandom() < 0.5)
	{
		pdfDirection = hittableMix.generate();
	}
	else
	{
		pdfDirection = scatterRec.pdfPointer->generate();
	}


	scattered = Ray(rec.p,pdfDirection);
	Vec3 dir = scattered.direction();
	float pdfVal = hittableMix.value(dir) * 0.5 + 0.5 * scatterRec.pdfPointer->value(dir);
;
	float scV = rec.mat->scatteringPdf(r, rec, scattered);
	return emitted + scatterRec.attenuation * scV * (color(scattered, tree, depth +1 )/pdfVal);
	
}

void Scene::render(std::string filepath, int height, int width , int rayPerPixel)
{
	Image im(height, width );
	std::uniform_real_distribution<> dis(0, 1);
	std::random_device rd;
	std::mt19937 gen;


	for (int j = 0; j < height; j++)
	{
		for (int i = 0; i < width; i++)
		{
			Color col(0, 0, 0);
			for (int k = 0; k < rayPerPixel; k++)
			{

				float u = float(i + dis(gen)) / float(width);
				float v = float(j + dis(gen)) / float(height);
				Ray r = cam.getRay(u, v);
				Color addedColor = color(r, sceneTree, 0);

				col += addedColor;



			}
			col = col / rayPerPixel;
			col.clamp();
			col = Color(pow(col.r, 1 / 2.2), pow(col.g, 1 / 2.2), pow(col.b, 1 / 2.2));

			im.setPixel(j, i, col);



		}

	}
	im.reversePixels();
	im.toPngFile(filepath);


}

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

void Scene::buildBVH()
{
	sceneTree = sceneTree.build(Objects, 0, 3);
	BVHinitialized = true;
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

