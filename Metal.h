#pragma once
#include "Material.h"
#include "vec3.h"
class Metal : public Material 
{

public:

	Metal(const Color& alb ,float f =0);
	bool scatter(Ray& rayIn, HitRecord& rec, Color& attenuation, Ray& scattered);

private:
	Color albedo;
	float fuzz;

};

