#pragma once
#include "Material.h"
#include "vec3.h"
#include "Texture.h"
class Metal : public Material 
{

public:

	Metal(std::shared_ptr<Texture> tex,float f =0);
	bool scatter(Ray& rayIn, HitRecord& rec, Color& attenuation, Ray& scattered);

private:
	std::shared_ptr<Texture> texture;
	float fuzz;

};

