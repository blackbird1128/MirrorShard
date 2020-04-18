#pragma once
#include "vec3.h"
#include "Material.h"
#include "Color.h"


class Lambertian : public Material
{
public:
	Lambertian(Color albed);
	bool scatter(Ray& rayIn, HitRecord& rec, Color& attenuation, Ray& scattered);


private:
	Color albedo;

};



