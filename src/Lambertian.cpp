#include "Lambertian.h"
#include "MathUtils.hpp"
#include "ONB.h"
#include "cosinePdf.h"
#include <random>



Lambertian::Lambertian(std::shared_ptr<Texture> tex)
{
	matTexture = tex;

}

bool Lambertian::scatter(Ray& rayIn, HitRecord& rec, scatterRecord& scatterRec,  Ray& scattered  )
{
	ONB uvw;
	uvw.buildFromW(rec.normal);
	Vec3 direction = uvw.local(utils::randomCosineDirection());
	scatterRec.attenuation  = matTexture->getColor(rec.u, rec.v);
	scatterRec.pdfPointer = std::move(std::make_unique<cosinePdf>(rec.normal));
	return true;
}

float Lambertian::scatteringPdf(Ray& rayIn, HitRecord& rec, Ray& scattered)
{
	float cosine = dot(rec.normal, unitVector(scattered.direction()));
	return cosine < 0 ? 0 : cosine / 3.14159;
}

bool Lambertian::isSpecular()
{
	return false;
}






