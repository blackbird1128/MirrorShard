#include "Metal.h"
#include "MathUtils.hpp"
#include <random>
Metal::Metal(std::shared_ptr<Texture> tex, float f)
{

	texture = tex;
	fuzz = f;
}

bool Metal::scatter(Ray& rayIn, HitRecord& rec, scatterRecord& scatterRec, Ray& scattered)
{

	Vec3 reflected = reflect(unitVector(rayIn.direction()), rec.normal);
	scatterRec.specular_ray = Ray(rec.p, reflected + fuzz * utils::randomInUnitSphere());
	scatterRec.attenuation = texture->getColor(rec.u , rec.v);
	scatterRec.pdfPointer = nullptr;
	return true;

}

bool Metal::isSpecular()
{
	return true;
}


