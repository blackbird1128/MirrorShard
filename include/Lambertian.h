#pragma once
#include <memory>
#include "vec3.h"
#include "Material.h"
#include "Color.h"
#include "Texture.h"

class Lambertian : public Material
{
public:
	Lambertian(std::shared_ptr<Texture> tex);
	bool scatter(Ray& rayIn, HitRecord& rec, Color& attenuation, Ray& scattered);


private:
	std::shared_ptr<Texture> matTexture;

};



