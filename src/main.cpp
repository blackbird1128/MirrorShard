#include <iostream>
#include <fstream>
#include <limits>
#include <memory>
#include <random>
#include <chrono>
#include <math.h> 
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

Color color(Ray& r, Scene& word, int depth  )
{
	HitRecord rec;
	if (word.hit(r , 0.001, std::numeric_limits<float>::max(),rec))
	{
		Ray scattered;
		Color attenuation;
		
		if (depth < 50 && rec.mat->scatter(r, rec, attenuation, scattered))
		{
			depth += 1;
			return attenuation * color(scattered, word, depth );

		}
		else
		{

			return Color(0,0,0);
		}


	}
	else
	{

		Vec3 unitDirection = unitVector(r.direction());
		float t = 0.5 * (unitDirection.y + 1.0);
		return (1.0 - t) * Color(1.0, 1.0, 1.0) + t * Color(0.5, 0.7, 1.0);
	}
}




int main()
{

	float scaleFactor =  3;
	int nx = 160*scaleFactor;
	int ny = 90*scaleFactor;
	int nr =  100;


	Vec3 a(2, 3, 4);
	Vec3 b(5, 6, 7);
	std::cout << a.crossProduct(b) << "\n";

	Image im( ny, nx );




	std::uniform_real_distribution<> dis(0, 1);
	std::random_device rd;
	std::mt19937 gen;

	auto t0 = std::make_unique<Triangle>(Vec3(-1, -1, -1), Vec3(1, -1, -1), Vec3(0, 1, -1));
	t0->setMaterial(std::make_shared<Metal>(Color(0.2, 0.3, 0.5)));
	auto s1 = std::make_unique<Sphere>(Vec3(0.0, 0, -1), 0.5);
	s1->setMaterial(std::make_shared<Dialectric>(1.5)  ) ;


	auto sv = std::make_unique<Sphere>(Vec3(0.0, 0, -3.3), 0.2);
	sv->setMaterial(std::make_shared<Metal>(Color(0.2,0.3,0.5)));

	auto s2 = std::make_unique<Sphere>(Vec3(0, -1000.5, -1.2), 1000);
	s2->setMaterial(std::make_shared<Lambertian>(Color (0.7, 0.2, 0.4)));



	auto s3 = std::make_unique<Sphere>(Vec3(0, 0, -4), 0.5);
	s3->setMaterial(std::make_shared<Lambertian>( Color(0.2,0.5,0.4) ));


	auto s4 = std::make_unique<Sphere>(Vec3(-1.2, 0, -1), 0.5);
	s4->setMaterial(std::make_shared<Lambertian>(Color(0.6 , 0.3 , 0.3)));


	auto s5 = std::make_unique<Sphere>(Vec3(1, 0, -1), 0.5);
	s5->setMaterial(std::make_shared<Lambertian>(Color(0.3, 0.7, 0.3)));

	Camera cam(Vec3(-2.0 , 2.0 ,1.0) , Vec3(0.0,0.0,-1.0) , Vec3(0,2,0) , 90 , float(nx)/float(ny));
	Scene mainScene;


	mainScene.addObject(std::move(t0));
	mainScene.addObject(std::move(s1));
	//mainScene.addObject(std::move(s2));
	/*
	mainScene.addObject(std::move(s3));
	mainScene.addObject(std::move(s5));
	mainScene.addObject(std::move(s4));
	mainScene.addObject(std::move(sv));
	*/

	std::chrono::time_point<std::chrono::system_clock> start, end;
	start = std::chrono::system_clock::now();

	for (int j = ny - 1; j >= 0; j--)
	{
		for (int i = 0; i < nx; i++)
		{
			Color col(0, 0, 0);
			for (int k = 0; k < nr; k++)
			{

				float u = float(i + dis(gen)) / float(nx);
				float v = float(j + dis(gen)) / float(ny);
				Ray r = cam.getRay(u, v);
				Color addedColor = color(r, mainScene, 0 );
				col += addedColor;



			}
			col = col / nr;
			col = Color(pow(col.r,1/2.2), pow(col.g,1/2.2), pow(col.b , 1/2.2));
			im.setPixel(j, i, col);



		}

	}
	im.toPpmFile("test10.ppm");
	end = std::chrono::system_clock::now();
	int elapsed_seconds = std::chrono::duration_cast<std::chrono::seconds>(end - start).count();
	std::cout << "elapsed time: " << elapsed_seconds << "s\n";

}