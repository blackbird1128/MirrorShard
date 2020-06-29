#pragma once
#include "Material.h"
class Light :
public Material
{
public :
	Light(Color& emissive);
	bool scatter(Ray& rayIn, HitRecord& rec, Color& attenuation, Ray& scattered);
	Color getEmissive();
private:
	Color emissive;

};

