#pragma once
#include "Material.h"
#include "vec3.h"
class Metal : public Material 
{

public:

	Metal(const Vec3& alb ,float f =0);
	bool scatter(Ray& rayIn, HitRecord& rec, Vec3& attenuation, Ray& scattered);

private:
	Vec3 albedo;
	float fuzz;

};

