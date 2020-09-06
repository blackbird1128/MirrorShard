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
#include "OrenNayar.h"
#include "cosinePdf.h"
#include "MixturePdf.h"
#include "CookTorance.h"


std::vector<std::shared_ptr<Triangle>> createQuad(Vec3 firstPoint , Vec3 secondPoint , Vec3 thirdPoint , Vec3 fourthPoint)
{

	std::vector<std::shared_ptr<Triangle>> result;
	auto t1 = std::make_shared<Triangle>(firstPoint, thirdPoint, fourthPoint);
	t1->setMaterial(std::make_shared<Lambertian>(std::make_shared<ColorTexture>(0.2, 0.2, 0.2)));
	auto t2 = std::make_shared<Triangle>(firstPoint, secondPoint, fourthPoint);
	t2->setMaterial(std::make_shared<Lambertian>(std::make_shared<ColorTexture>(0.2, 0.2, 0.2)));
	result.push_back(t1);
	result.push_back(t2);
	return result;

}




int main()
{
	BVHNode node;

	float scaleFactor = 1.0;
	int nx = 1080*scaleFactor;
	int ny = 960*scaleFactor;
	

	Image rought(0,0);
	rought.loadFromFile("MyriamB.jpg");
	rought.toPngFile("finger3.png");
	ParameterMap roughtMap(rought, 0.5);


	auto s2 = std::make_shared<Sphere>(Vec3(0, -1000.5, -1.2), 1000);
	s2->setMaterial(std::make_shared<Lambertian>(std::make_shared<ColorTexture>(0.5,0.5,0.7)));
	//s2->setMaterial(std::make_shared<CookTorance>(0.03, 1.53, std::make_shared<ColorTexture>(0.5, 0.5, 0.7)));

	auto s3 = std::make_shared<Sphere>(Vec3(20, 300, 0), 20);
	s3->setMaterial(std::make_shared<Light>(Color(10, 10, 10)));

	//auto s4 = std::make_shared<Sphere>(Vec3(-3000, 4000, 4000), 900);
	//s4->setMaterial(std::make_shared<Light>(Color(15, 15, 15)));


	auto s5 = std::make_shared<Sphere>(Vec3(70, 45, 40), 45);
	s5->setMaterial(std::make_shared<CookTorance>(roughtMap, Vec3(0.15557, 0.42415, 1.3831), Vec3(3.6024, 2.4721, 1.9155), std::make_shared<ColorTexture>(0.5, 0.5, 0.7)));


	auto s10 = std::make_shared<Sphere>(Vec3(0.0, 0.0, 0.0), 100000);
	s10->setMaterial(std::make_shared<Lambertian>(std::make_shared<ColorTexture>(0.5, 0.5, 0.7)));


	auto bigSphere = std::make_shared<Sphere>(Vec3(70, 45, 40), 45);
	bigSphere->setMaterial(std::make_shared<CookTorance>( 0.2, Vec3(0.15557, 0.42415, 1.3831), Vec3(3.6024, 2.4721, 1.9155), std::make_shared<ColorTexture>(0.5, 0.5, 0.7)));
	//Camera cam(Vec3(  -920 , 850 , 1150 ) , Vec3( 0 , 600 , 0 ) , Vec3(0,1,0) , 45 , float(nx)/float(ny)); // lucy camera 
	Camera cam(Vec3(0, 300,300), Vec3(0, 20, 0), Vec3(0, 1, 0), 45, float(nx) / float(ny));
	std::vector<HittablePtr> sampled;
	sampled.push_back(s3);

	Scene mainScene(cam , sampled);
	Model LucyModel;
	LucyModel.loadFromFile("Myriam.obj");
	LucyModel.setMaterial(std::make_shared<CookTorance>(0.07,Vec3(0.23780, 1.0066, 1.2453) ,Vec3(3.6264, 2.5823, 2.3478), std::make_shared<ColorTexture>(0.5, 0.5, 0.7)));
   // LucyModel.setMaterial(std::make_shared<Lambertian>(std::make_shared<ImageTexture>("MyriamB.png")));
	mainScene.addObject(std::move(s2));
	mainScene.addObject(std::move(s3));
	mainScene.addObject(std::move(LucyModel));
	mainScene.addObject(std::move(s5));
	//mainScene.addObject(std::move(bigSphere));
	mainScene.buildBVH();
	std::cout << "start rendering" << std::endl;
	std::chrono::time_point<std::chrono::system_clock> start, end;
	start = std::chrono::system_clock::now();
	mainScene.render("testroughMap.png" , ny , nx ,16);
	end = std::chrono::system_clock::now();
	int elapsed_seconds = std::chrono::duration_cast<std::chrono::seconds>(end - start).count();
	std::cout << "elapsed time: " << elapsed_seconds << "seconds \n";
	//std::cout << "ray per second : " << 960 * 1080 * 16 / elapsed_seconds;
	return 0;

}