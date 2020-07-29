#pragma once
#include "Material.h"




class Dialectric : public Material
{
public:
	Dialectric(float sdIndex , Color  albed = Color(1, 1, 1));
	float shlick(float cosine, float refIndex);
	bool  refract(const Vec3& v, Vec3& n, float niOverNt, Vec3& refracted);
	bool scatter(Ray& rayIn, HitRecord& rec, scatterRecord& scatterRec, Ray& scattered) override;
	bool isSpecular() override;

	float refractiveIndex;
	Color albedo;
};

