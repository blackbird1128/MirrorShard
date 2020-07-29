#pragma once
#include <memory>
#include "vec3.h"
#include "Material.h"
#include "Color.h"
#include "Texture.h"
#include "pdf.h"

class Lambertian : public Material
{
public:
	Lambertian(std::shared_ptr<Texture> tex);
	bool  scatter(Ray& rayIn, HitRecord& rec, scatterRecord& scatterRec, Ray& scattered  ) override;
	float scatteringPdf(Ray& rayIn, HitRecord& rec, Ray& scattered) override;
	bool  isSpecular() override;

private:
	std::shared_ptr<Texture> matTexture;

};



