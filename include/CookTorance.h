#pragma once
#include "Material.h"
#include "Texture.h"
#include <memory>
#include <cmath>
class CookTorance : public Material
{
public:
	CookTorance(float roughness, float ior ,  std::shared_ptr<Texture> tex);
	bool  scatter(Ray& rayIn, HitRecord& rec, scatterRecord& scatterRec, Ray& scattered) override;
	Color scatteringPdf(Ray& rayIn, HitRecord& rec, Ray& scattered) override;
	bool  isSpecular() override;
	float fresnelApproximation(float ior , float absorbtionCoef, Ray& rayIn, HitRecord& rec , Ray& scattered);
	float positiveCaracteristic(float x);
	float ggxNormalDistribution(float NdotH, float roughness);
	float schlickMaskingTerm(float NdotL, float NdotV, float roughness);
	Vec3 getGGXMicrofacet(float roughtness, Vec3 normal);
	float G(Vec3 inDirection, Vec3 outDirection, Vec3 m, Vec3 n);
	float G1(Vec3 v, Vec3 m, Vec3 n);
	float D(Vec3 m, Vec3 n);
	Color shlick(float cosine, Color R0);
	Vec3 FresnelDieletricConductor(Vec3 Eta, Vec3 Etak, float CosTheta)
	{
		float CosTheta2 = CosTheta * CosTheta;
		float SinTheta2 = 1 - CosTheta2;
		Vec3 Eta2 = Eta * Eta;
		Vec3 Etak2 = Etak * Etak;

		Vec3 t0 = Eta2 - Etak2 - Vec3(1,1,1)*  SinTheta2;
		Vec3 a2plusb2 = Vec3(sqrt(t0.x * t0.x + 4 * Eta2.x * Etak2.x), sqrt(t0.y * t0.y + 4 * Eta2.y * Etak2.y), sqrt(t0.z * t0.z + 4 * Eta2.z * Etak2.z));
		Vec3 t1 = a2plusb2 + Vec3(1,1,1) * CosTheta2;
		Vec3 a = Vec3(sqrt(0.5f * (a2plusb2.x + t0.x)), sqrt(0.5f * (a2plusb2.y + t0.y)), sqrt(0.5f * (a2plusb2.z + t0.z)));
		Vec3 t2 = 2 * a * CosTheta;
		Vec3 Rs = (t1 - t2) / (t1 + t2);

		Vec3 t3 = CosTheta2 * a2plusb2 + (Vec3(1,1,1)*  SinTheta2 * SinTheta2);
		Vec3 t4 = t2 * SinTheta2;
		Vec3 Rp = Rs * (t3 - t4) / (t3 + t4);

		return 0.5 * (Rp + Rs);
	}

private:

	std::shared_ptr<Texture> matTexture;
	float roughtParameter;
	float matIor;
	Vec3 m; //initialized in scatter -> need to be refactored
	Color specularFresnelColor;



};

