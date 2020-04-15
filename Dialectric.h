#pragma once
#include "Material.h"




class Dialectric : public Material
{
public:
	Dialectric(float sdIndex , Vec3  albed = Vec3(1, 1, 1));
	float shlick(float cosine, float refIndex);
	bool  refract(const Vec3& v, Vec3& n, float niOverNt, Vec3& refracted);
	bool scatter(Ray& rayIn, HitRecord& rec, Vec3& attenuation, Ray& scattered);


	float refractiveIndex;
	Vec3 albedo;
};

