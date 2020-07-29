#pragma once
#include "Ray.h"
#include "Hitable.h"
#include "Color.h"
#include "pdf.h"
class HitRecord;

struct scatterRecord {
	Ray specular_ray;
	Color attenuation;
	std::unique_ptr<pdf> pdfPointer;
};



class Material
{
public:
	virtual bool scatter(Ray& rayIn, HitRecord& rec, scatterRecord& scatterRec, Ray& scattered )
	{
		return false;
	};
	virtual float scatteringPdf(Ray& rayIn , HitRecord& rec , Ray& scattered)
	{
		return 0.0;
	}
	virtual Color getEmissive()
	{
		return Color(0, 0, 0);
	};

	virtual bool isSpecular() = 0;

};


Vec3 reflect(const Vec3& v, const Vec3& unitV);


