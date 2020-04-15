#include <iostream>
#include <fstream>
#include <limits>
#include <memory>
#include <random>
#include <chrono>
#include "vec3.h"
#include "Ray.h"
#include "Scene.h"
#include "Sphere.h"
#include "Camera.h"
#include "Lambertian.h"
#include "Metal.h"
#include "Dialectric.h"




Vec3 color(Ray& r , Scene& word , int depth)
{
	HitRecord rec;
	if (word.hit(r , 0.015, std::numeric_limits<float>::max(),rec))
	{
		Ray scattered;
		Vec3 attenuation;
	
		if (depth < 500 && rec.mat->scatter(r, rec, attenuation, scattered))
		{
			depth += 1;
			return attenuation * color(scattered, word, depth );

		}
		else
		{

			return Vec3(0,0,0);
		}


	}
	else
	{
		Vec3 unitDirection = unitVector(r.direction());
		float t = 0.5 * (unitDirection.y + 1.0);
		return (1.0 - t) * Vec3(1.0, 1.0, 1.0) + t * Vec3(0.5, 0.7, 1.0);
	}
}




int main()
{
	float scaleFactor = 1;
	int nx = 200 * scaleFactor;
	int ny = 100 * scaleFactor;
	int nr =  150;


	std::ofstream ppmFile;
	ppmFile.open("test6.ppm");

	std::uniform_real_distribution<> dis(0, 0.9);
	std::random_device rd;
	std::mt19937 gen;

	auto s1 = std::make_unique<Sphere>(Vec3(0.0, 0, -1), 0.5);
	s1->setMat(std::make_shared<Dialectric>(1.32009)  ) ;

	auto s2 = std::make_unique<Sphere>(Vec3(0, -1000.5, -1.2), 1000);
	s2->setMat(std::make_shared<Lambertian>(Vec3(0.7, 0.2, 0.4)  )  );



	auto s3 = std::make_unique<Sphere>(Vec3(0, 0, -5), 0.5);
	s3->setMat(std::make_shared<Lambertian>( Vec3(0.2,0.5,0.4) ));


	auto s4 = std::make_unique<Sphere>(Vec3(-1, 0, -1), 0.5);
	s4->setMat(std::make_shared<Metal>(Vec3(0.3 , 0.3 , 0.3) , 0.123));

	Camera cam(Vec3(-2.0 , 2.0 ,1.0) , Vec3(0.0,0.0,-1.0) , Vec3(0,2,0) , 90 , float(nx)/float(ny));
	Scene mainScene;

	mainScene.addObject(std::move(s1));
	mainScene.addObject(std::move(s2));
	mainScene.addObject(std::move(s3));
	mainScene.addObject(std::move(s4));

	ppmFile << "P3\n" << nx << " " << ny << "\n255\n"; 

	for (int j = ny - 1; j >= 0; j--)
	{
		for (int i = 0; i < nx; i++)
		{
			Vec3 col(0, 0, 0);
			for (int k = 0; k < nr; k++)
			{

				float u = float(i + dis(gen)) / float(nx);
				float v = float(j + dis(gen)) / float(ny);
				Ray r = cam.getRay(u, v);
				col += color(r, mainScene,0);

			}
			col = col / nr;
			col = Vec3(pow(col.x,1/2.2), pow(col.y,1/2.2), pow(col.z , 1/2.2));
			int ir = int(255.99 * col.x);
			int ig = int(255.99 * col.y);
			int ib = int(255.99 * col.z);

			ppmFile << ir << " " << ig << " " << ib << "\n";


		}

	}

}