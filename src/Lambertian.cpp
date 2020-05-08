#include "Lambertian.h"
#include "MathUtils.hpp"
#include <random>



Lambertian::Lambertian(Color albed)
{
	albedo = albed;

}

bool Lambertian::scatter(Ray& rayIn, HitRecord& rec, Color& attenuation, Ray& scattered)
{
	Vec3 target = rec.p + rec.normal + utils::randomInUnitSphere();
	scattered = Ray(rec.p, target - rec.p);
	attenuation = (albedo - attenuation);
	return true;
}




