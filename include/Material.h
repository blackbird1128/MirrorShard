#pragma once
#include "Ray.h"
#include "Hitable.h"
#include "Color.h"
class HitRecord;

class Material
{
public:
	virtual bool scatter(Ray& rayIn, HitRecord& rec, Color& attenuation, Ray& scattered) = 0;
	virtual Color getEmissive()
	{
		return Color(0, 0, 0);
	};
};


Vec3 reflect(const Vec3& v, const Vec3& unitV);


