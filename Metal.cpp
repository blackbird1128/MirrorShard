#include "Metal.h"
#include "MathUtils.hpp"
#include <random>
Metal::Metal(const Vec3& alb, float f)
{

	albedo = alb;
	fuzz = f;
}



bool Metal::scatter(Ray& rayIn, HitRecord& rec, Vec3& attenuation, Ray& scattered)
{
	
	Vec3 reflected = reflect(unitVector(rayIn.direction()), rec.normal);

	Vec3 rdInSphere = utils::randomInUnitSphere();

	scattered = Ray(rec.p, reflected + fuzz * rdInSphere );


	attenuation = albedo;
	return (dot(scattered.direction(), rec.normal) > 0);
}


