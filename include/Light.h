#pragma once
#include "Material.h"
class Light :
public Material
{
public :
	Light(Color& emissive);
	bool scatter(Ray& rayIn, HitRecord& rec, scatterRecord& scatterRec , Ray& scattered) override;
	Color getEmissive() override;
	bool isSpecular() override;
private:
	Color emissive;

};

