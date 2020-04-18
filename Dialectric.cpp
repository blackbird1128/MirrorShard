#include "Dialectric.h"
#include "Material.h"
#include "MathUtils.hpp"

Dialectric::Dialectric(float sdIndex , Color  albed )
{
	refractiveIndex = sdIndex;
	albedo = albed;
}

float Dialectric::shlick(float cosine, float refIndex)
{
	float r0 = (1 - refIndex) / (1 + refIndex);
	r0 = r0 * r0;
	return r0 + (1 - r0) * pow(1 - cosine, 5);
}

bool Dialectric::refract(const Vec3& v, Vec3& n, float niOverNt, Vec3& refracted)
{
	Vec3 uv = unitVector(v);
	float dt = dot(uv, n);
	float dt2 = dt * dt;
	float discriminant = 1.0 - niOverNt * niOverNt * (1 - dt2 );

	if (discriminant > 0)
	{
		refracted = niOverNt * (uv - n * dt) - n * sqrt(discriminant);
		return true;
	}
	else
	{
		return false;
	}
}

bool Dialectric::scatter(Ray& rayIn, HitRecord& rec, Color& attenuation, Ray& scattered)
{
	Vec3 outwardNormal;
	Vec3 reflected = reflect(rayIn.direction(), rec.normal);
	float niOverNt;
	attenuation = albedo;
	Vec3 refracted;
	float cosine;
	float reflectProb;


	if (dot(rayIn.direction(), rec.normal) > 0)
	{
		outwardNormal = -rec.normal;
		niOverNt =  refractiveIndex;
		cosine = dot(unitVector(rayIn.direction()), rec.normal);
	}
	else
	{
		outwardNormal = rec.normal;
		niOverNt = (1 / refractiveIndex);
		cosine = -dot(unitVector(rayIn.direction()), rec.normal);
	}

	if (refract(rayIn.direction(), outwardNormal, niOverNt, refracted))
	{
		reflectProb = shlick(cosine, refractiveIndex);
		
	}
	else
	{

		reflectProb = 1;

	}


	if (utils::quickRandom() < reflectProb) {
		scattered = Ray(rec.p, reflected);
	}
	else {
		scattered = Ray(rec.p, refracted);
	}
	return true;



}
