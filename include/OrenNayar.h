#pragma once
#include "Material.h"
#include "Texture.h"
#include <memory>
class OrenNayar : public Material
{

public:
	OrenNayar(float  roughness,  std::shared_ptr<Texture> tex) 
	{
		matTexture = tex;
		A = 1.0 - 0.5 * ((roughness * roughness) / (roughness * roughness + 0.33));
		B = 0.45 * (roughness * roughness) / (roughness * roughness + 0.09);
	
	}
	bool  scatter(Ray& rayIn, HitRecord& rec, scatterRecord& scatterRec, Ray& scattered) override;
	Color scatteringPdf(Ray& rayIn, HitRecord& rec, Ray& scattered) override;
	bool  isSpecular() override;



private:

	std::shared_ptr<Texture> matTexture;
	float A;
	float B;

};

