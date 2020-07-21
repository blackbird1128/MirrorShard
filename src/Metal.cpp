#include "Metal.h"
#include "MathUtils.hpp"
#include <random>
Metal::Metal(std::shared_ptr<Texture> tex, float f)
{

	texture = tex;
	fuzz = f;
}

bool Metal::scatter(Ray& rayIn, HitRecord& rec, Color& attenuation, Ray& scattered)
{
	
	Vec3 reflected = reflect(unitVector(rayIn.direction()), rec.normal);
	scattered = Ray(rec.p, reflected + fuzz * utils::randomInUnitSphere());
	attenuation = texture->getColor(rec.u , rec.v);
	return (dot(scattered.direction(), rec.normal) > 0);

}


