#pragma once
#include "Material.h"
#include "Texture.h"
#include "ParameterMap.h"
#include <memory>
#include <cmath>
class CookTorance : public Material
{
public:
	CookTorance(float roughness, Vec3 ior , Vec3 kIor ,  std::shared_ptr<Texture> tex);
	CookTorance(ParameterMap roughness, Vec3 ior, Vec3 kIor, std::shared_ptr<Texture> tex);
	bool  scatter(Ray& rayIn, HitRecord& rec, scatterRecord& scatterRec, Ray& scattered) override;
	Color scatteringPdf(Ray& rayIn, HitRecord& rec, Ray& scattered) override;
	bool  isSpecular() override;
	float fresnelApproximation(float ior , float absorbtionCoef, Ray& rayIn, HitRecord& rec , Ray& scattered);
	float positiveCaracteristic(float x);
	float ggxNormalDistribution(float NdotH, float roughness);
	Vec3 getGGXMicrofacet(float roughtness, Vec3 normal);
	float G(Vec3 inDirection, Vec3 outDirection, Vec3 m, Vec3 n,float roughness);
	float G1(Vec3 v, Vec3 m, Vec3 n,float roughness);
	float D(Vec3 m, Vec3 n);
	Color shlick(float cosine, Color R0);


private:

	std::shared_ptr<Texture> matTexture;
	float roughtParameter;
	ParameterMap roughtnessMap;
	Vec3 matIor;
	Vec3 matIorAbsorbtion;
	Vec3 m; //initialized in scatter -> need to be refactored




};

