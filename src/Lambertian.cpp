#include "Lambertian.h"
#include "MathUtils.hpp"
#include <random>



Lambertian::Lambertian(std::shared_ptr<Texture> tex)
{
	matTexture = tex;

}

bool Lambertian::scatter(Ray& rayIn, HitRecord& rec, Color& attenuation, Ray& scattered)
{
	Vec3 target = rec.p + rec.normal + utils::randomInUnitSphere();
	scattered = Ray(rec.p, target - rec.p);
	attenuation = matTexture->getColor(rec.u , rec.v);
	return true;
}




