#include <iostream>
#include <fstream>
#include <limits>
#include <memory>
#include <random>
#include <chrono>
#include <cmath>
#include "vec3.h"
#include "Ray.h"
#include "Scene.h"
#include "Sphere.h"
#include "Camera.h"
#include "Lambertian.h"
#include "Metal.h"
#include "Dialectric.h"
#include "Color.h"
#include "MathUtils.hpp"
#include "Image.h"
#include "Triangle.h"
#include "Model.h"
#include "MathUtils.hpp"
#include "BVHNode.h"
#include "Light.h"
Color color(Ray& r, BVHNode& tree, int depth)
{
	HitRecord rec;
	if (depth > 50)
	{
		return Color(0, 0, 0);
	}
	if (!tree.hit(r, 0.001, std::numeric_limits<float>::max(), rec))
	{
		return (Color(0, 0, 0));
	}


	Ray scattered;
	Color attenuation;
	Color emitted = rec.mat->getEmissive();
	if (!rec.mat->scatter(r, rec, attenuation, scattered))
	{
		return emitted;
	}
	return emitted + attenuation * color(scattered, tree, depth +1 );
}

int main()
{
	BVHNode node;

	float scaleFactor = 1;
	int nx = 1080*scaleFactor;
	int ny = 960*scaleFactor;
	int nr =  400;

	std::uniform_real_distribution<> dis(0, 1);
	std::random_device rd;
	std::mt19937 gen;


	auto s2 = std::make_shared<Sphere>(Vec3(0, -1000.5, -1.2), 1000);
	s2->setMaterial(std::make_shared<Lambertian>(Color(0.5,0.5,0.7)));


	auto s3 = std::make_shared<Sphere>(Vec3(3000, 4000, -4000), 2200);
	s3->setMaterial(std::make_shared<Light>(Color(12, 12, 12)));

	auto s4 = std::make_shared<Sphere>(Vec3(-3000, 4000, -4000), 2200);
	s4->setMaterial(std::make_shared<Light>(Color(15, 15, 15)));

	Camera cam(Vec3(  -920 , 1800 , 1350 ) , Vec3( 0 , 600 , 0 ) , Vec3(0,1,0) , 45 , float(nx)/float(ny));
	Scene mainScene;
	Model LucyModel;
	LucyModel.loadFromFile("lucy.obj");
	LucyModel.setMaterial(std::make_shared<Lambertian>(Color(0.4,0.4,0.5)));
	mainScene.addObject(std::move(s2));
	mainScene.addObject(std::move(s3));
	mainScene.addObject(std::move(s4));
	mainScene.addObject(std::move(LucyModel));
	int minNodeSize = 3;;
	node = node.build(mainScene.Objects, 0, minNodeSize );

	std::cout << "start rendering" << std::endl;
	std::chrono::time_point<std::chrono::system_clock> start, end;
	start = std::chrono::system_clock::now();
	Image im(ny, nx);




	for (int j = ny   ; j >= 0; j--)
	{
		for (int i = 0; i < nx; i++)
		{
			Color col(0, 0, 0);
			for (int k = 0; k < nr; k++)
			{

				float u = float(i + dis(gen)) / float(nx);
				float v = float(j + dis(gen)) / float(ny);
				Ray r = cam.getRay(u, v);
				Color addedColor = color(r, node, 0 );

				col += addedColor;



			}
			col = col / nr;
			col.clamp();
			col = Color(pow(col.r,1/2.2), pow(col.g,1/2.2), pow(col.b , 1/2.2));
			
			im.setPixel(j, i, col);



		}

	}
	im.toPpmFile("test20.ppm");
	end = std::chrono::system_clock::now();
	int elapsed_seconds = std::chrono::duration_cast<std::chrono::seconds>(end - start).count();
	std::cout << "elapsed time: " << elapsed_seconds << "s\n";

}