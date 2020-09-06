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

	scatterRec.attenuation  = matTexture->getColor(rec.u, rec.v);
	scatterRec.pdfPointer = std::move(std::make_unique<cosinePdf>(rec.normal));
	return true;
}

Color Lambertian::scatteringPdf(Ray& rayIn, HitRecord& rec, Ray& scattered)
{
	float cosine = dot(rec.normal, unitVector(scattered.direction()));
	float a  =  cosine < 0 ? 0 : cosine / 3.14159;
	return Color(a, a, a);
}

bool Lambertian::isSpecular()
{
	return false;
}






