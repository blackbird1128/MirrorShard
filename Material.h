#pragma once
#include "Ray.h"
#include "Hitable.h"

class HitRecord;

class Material
{
public:
	virtual bool scatter(Ray& rayIn, HitRecord& rec, Vec3& attenuation, Ray& scattered) = 0;

};


Vec3 reflect(const Vec3& v, const Vec3& unitV);


