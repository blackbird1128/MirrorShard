#include "OrenNayar.h"
#include "MathUtils.hpp"
#include "ONB.h"
#include "cosinePdf.h"

bool OrenNayar::scatter(Ray& rayIn, HitRecord& rec, scatterRecord& scatterRec, Ray& scattered)
{
	ONB uvw;
	uvw.buildFromW(rec.normal);
	Vec3 direction = uvw.local(utils::randomCosineDirection());
	scatterRec.attenuation = matTexture->getColor(rec.u, rec.v);
	scatterRec.pdfPointer = std::move(std::make_unique<cosinePdf>(rec.normal));
	return true;
}



float OrenNayar::scatteringPdf(Ray& rayIn, HitRecord& rec, Ray& scattered)
{
	float lightCosine = dot(rec.normal, unitVector(scattered.direction())); // cos 0i
	float camCosine = dot(rec.normal, unitVector(rayIn.direction())); // cos 0r
	float Oi = std::acos(lightCosine);
	float Or = std::acos(camCosine);

	float alpha = std::max(Oi, Or);
	float beta = std::min(Oi, Or);
	float result = lightCosine/ 3.14159265 * (A + (B * std::max(0.0f, cos(Oi - Or))) * sin(alpha) * tan(beta));
	return std::max(0.0f, result);
}
bool OrenNayar::isSpecular()
{
	return false;
}
