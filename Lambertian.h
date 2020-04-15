#pragma once
#include "vec3.h"
#include "Material.h"

class Lambertian : public Material
{
public:
	Lambertian(Vec3 albed);
	bool scatter(Ray& rayIn, HitRecord& rec, Vec3& attenuation, Ray& scattered);


private:
	Vec3 albedo;

};



