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
#include "ColorTexture.h"
#include "ImageTexture.h"

#include "cosinePdf.h"
#include "MixturePdf.h"

int main()
{
	BVHNode node;

	float scaleFactor = 1;
	int nx = 1080*scaleFactor;
	int ny = 960*scaleFactor;
	int nr =  256;

	





	auto s2 = std::make_shared<Sphere>(Vec3(0, -1000.5, -1.2), 1000);
	s2->setMaterial(std::make_shared<Lambertian>(std::make_shared<ColorTexture>(0.5,0.5,0.7)));


	auto s3 = std::make_shared<Sphere>(Vec3(3000, 4000, -4000), 200);
	s3->setMaterial(std::make_shared<Light>(Color(12, 12, 12)));

	auto s4 = std::make_shared<Sphere>(Vec3(-3000, 4000, 4000), 200);
	s4->setMaterial(std::make_shared<Light>(Color(15, 15, 15)));

	// Camera cam(Vec3(  -920 , 1800 , 1350 ) , Vec3( 0 , 600 , 0 ) , Vec3(0,1,0) , 45 , float(nx)/float(ny)); // lucy camera 
	Camera cam(Vec3(0, 300,300), Vec3(0, 20, 0), Vec3(0, 1, 0), 45, float(nx) / float(ny));
	std::vector<HittablePtr> sampled;
	sampled.push_back(s3);
	sampled.push_back(s4);
	Scene mainScene(cam , sampled);
	Model LucyModel;
	LucyModel.loadFromFile("Myriam.obj");
	LucyModel.setMaterial(std::make_shared<Lambertian>(std::make_shared<ImageTexture>("MyriamB.png")));
	mainScene.addObject(std::move(s2));
	mainScene.addObject(std::move(s3));
	mainScene.addObject(std::move(s4));
	mainScene.addObject(std::move(LucyModel));
	mainScene.buildBVH();
	std::cout << "start rendering" << std::endl;
	std::chrono::time_point<std::chrono::system_clock> start, end;
	start = std::chrono::system_clock::now();
	mainScene.render("testScene4.png" , 960 , 1080 , 16);
	end = std::chrono::system_clock::now();
	int elapsed_seconds = std::chrono::duration_cast<std::chrono::seconds>(end - start).count();
	std::cout << "elapsed time: " << elapsed_seconds << "s\n";
	return 0;



   /*
	int minNodeSize = 3;
	node = node.build(mainScene.Objects, 0, minNodeSize );

	std::cout << "start rendering" << std::endl;
	std::chrono::time_point<std::chrono::system_clock> start, end;
	start = std::chrono::system_clock::now();
	Image im(ny, nx);




	for (int j = 0 ; j < ny; j++)
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
	im.reversePixels();
	im.toPngFile("test1.png");
	end = std::chrono::system_clock::now();
	int elapsed_seconds = std::chrono::duration_cast<std::chrono::seconds>(end - start).count();
	std::cout << "elapsed time: " << elapsed_seconds << "s\n";
	*/
}