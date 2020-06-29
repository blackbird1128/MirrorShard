#include "Light.h"
#include "..\include\Light.h"

Light::Light(Color& emissive)
{
	this->emissive = emissive;
}

bool Light::scatter(Ray& rayIn, HitRecord& rec, Color& attenuation, Ray& scattered)
{
	return false;
}

Color Light::getEmissive()
{
	return emissive;
}
