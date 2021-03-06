#include "Scene.h"
#include "Sphere.h"
#include "Hitable.h"
#include "cosinePdf.h"
#include "hittablePdf.h"
#include "MixturePdf.h"
#include "MathUtils.hpp"
Color Scene::color(Ray& r, BVHNode& tree, int depth)
{


	HitRecord rec;
	if (depth > maxDepthParameter)
	{
		return Color(0, 0, 0);
	}
	if (!tree.hit(r, 0.001, std::numeric_limits<float>::max(), rec))
	{
		
		Vec3 unitDirection = unitVector(r.direction());
		float t = 0.5 * (unitDirection.y + 1.0);
		return (1.0 - t) * Color(1.0, 1.0, 1.0) + t * Color(0.5, 0.7, 1.0);
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
		
		return scatterRec.attenuation *  color(scatterRec.specular_ray, tree, depth + 1);
	}
	
	std::vector<pdfPtr> actualPdf;
	for (int i = 0 ; i < sampledPdf.size();i++)
	{
		sampledPdf[i].setOrigin(rec.p);
		pdfPtr temp = std::make_unique<hittablePdf>( sampledPdf[i]);
		actualPdf.push_back(std::move(temp));
	}
	
	float pdfVal;
	Vec3 dir;
	Vec3 pdfDirection;
	if (actualPdf.size() > 0)
	{

		MixturePdf hittableMix(std::move(actualPdf));


		if (utils::quickRandom() < 0.5)
		{
			pdfDirection = hittableMix.generate();
		}
		else
		{
			pdfDirection = scatterRec.pdfPointer->generate();
		}

		scattered = Ray(rec.p, pdfDirection);
		dir = scattered.direction();
		pdfVal = hittableMix.value(dir) * 0.5 + 0.5 * scatterRec.pdfPointer->value(dir);
	}
	else
	{
		dir = scattered.direction();
		scattered = Ray(rec.p, pdfDirection);
		pdfDirection = scatterRec.pdfPointer->generate();
		pdfVal = scatterRec.pdfPointer->value(dir);
	}
	Color scV = rec.mat->scatteringPdf(r, rec, scattered);
	return emitted + scatterRec.attenuation * scV * color(scattered, tree, depth +1 )/pdfVal;
	
}

void Scene::render(std::string filepath, int height, int width , int rayPerPixel)
{
	Image im(height, width );
	std::uniform_real_distribution<> dis(0, 1);
	std::random_device rd;
	std::mt19937 gen;

	int constRay = rayPerPixel;
	for (int j = 0; j < height; j++)
	{
		for (int i = 0; i < width; i++)
		{
			Color col(0, 0, 0);
			std::vector<Color> meanColor;  // used for quick importance sampling
			for (int k = 0; k < rayPerPixel; k++)
			{
				
				float u = float(i + dis(gen)) / float(width);
				float v = float(j + dis(gen)) / float(height);
				Ray r = cam.getRay(u, v);
				Color addedColor = color(r, sceneTree, 0);
				if (col.r != col.r)
				{
					col.r = 0;
 				}
				if (col.g != col.g)
				{
					col.g = 0;
				}
				if (col.b != col.b)
				{
					col.b = 0;
				}
				if (k <= 5 && constRay > 5)
				{

					meanColor.push_back(addedColor);

				}
				col += addedColor;
			}
			col = col / rayPerPixel;
			col = Color(pow(col.r, 1 / 2.2), pow(col.g, 1 / 2.2), pow(col.b, 1 / 2.2));
			col = col.clamp();
			im.setPixel(j, i, col);



		}

	}
	im.reversePixels();
	im.toPngFile(filepath);


}

Vec3 Scene::Uncharted2Tonemap(Vec3 x)
{
	// https://frictionalgames.blogspot.com/2012/09/tech-feature-hdr-lightning.html
	float A = 0.15;
	float B = 0.50;
	float C = 0.10;
	float D = 0.20;
	float E = 0.02;
	float F = 0.30;

	return ((x * (A * x + (Vec3(1, 1, 1) * C * B)) + (Vec3(1,1,1)* D * E)) / (x * (A * x + (Vec3(1,1,1)*B)) +(Vec3(1,1,1)*  D * F))) - (Vec3(1,1,1)*( E / F));
	
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

