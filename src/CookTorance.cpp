#include "CookTorance.h"
#include "MathUtils.hpp"
#include "GGXSmithPdf.h"
#include "ONB.h"
#include "cosinePdf.h"

CookTorance::CookTorance(float roughness, float ior  ,  std::shared_ptr<Texture> tex)
{
	roughtParameter = roughness;
	matIor = ior;
	matTexture = tex;
}

bool CookTorance::scatter(Ray& rayIn, HitRecord& rec, scatterRecord& scatterRec, Ray& scattered)
{

	 m = getGGXMicrofacet(roughtParameter , rec.normal );
	 Vec3 reflected = unitVector(reflect(unitVector(rayIn.direction()), unitVector(m)));
	 scatterRec.specular_ray = Ray(rec.p, reflected);



	scatterRec.attenuation = Color(1.0,1.0,1.0);

	//scatterRec.pdfPointer = std::move(std::make_unique<cosinePdf>(m));

	std::unique_ptr<GGXSmithPdf> GGXpdf = std::make_unique<GGXSmithPdf>(m, rec.normal, rayIn.direction()  , roughtParameter);


	scatterRec.pdfPointer = std::move(GGXpdf);

	return (dot(scatterRec.specular_ray.direction(),m ) > 0);
}

Color CookTorance::scatteringPdf(Ray& rayIn, HitRecord& rec, Ray& scattered)
{


		//std::cout << m << std::endl;

		Color F(fresnelApproximation(0.15557, 3.6024, rayIn, rec, scattered), fresnelApproximation(0.42415, 2.4721, rayIn, rec, scattered), fresnelApproximation(1.3831, 1.9155, rayIn, rec, scattered));
		//F =  shlick(dot(rayIn.direction(), m), Color(0.7, 0.7, 0.7));
		Vec3 F2 = FresnelDieletricConductor(Vec3(01, 01, 1.3831), Vec3(3.6024, 2.4721, 1.9155), dot(rayIn.direction(), m));
		//std::cout << F2 << std::endl; 
		//F = Color(F2.x, F2.y, F2.z);
		//F = Color(1.0, 1.0, 1.0);
		/*
		NdotL = abs(dot(rec.normal, L));
	    NdotV = abs(dot(rec.normal, rayIn.direction()));


		//scatterRec.pdfPointer = nullptr;
		Color ggxTerm = (D2 * Gt * F )/ (4 * NdotL * NdotV + 0.000001)  + Color(0.000000001, 0.000000001, 0.000000001) ;
		float firstTerm = positiveCaracteristic(dot(scattered.direction(), m) / dot(scattered.direction(), rec.normal));
		float cos0v = dot(unitVector(scattered.direction()), unitVector(rec.normal));
		float tan20v = (1 - cos0v * cos0v) / (cos0v * cos0v);
		std::cout << "tan2ov : " << tan20v << std::endl;
		float secondTerm = 2 /(1 + sqrt((1 + roughtParameter * roughtParameter * tan20v)));
		std::cout << firstTerm * secondTerm << std::endl;


		std::cout << "G : " << G(rayIn.direction(), scattered.direction(), m, rec.normal) << std::endl;
		std::cout << "D: " << D(m, rec.normal) << std::endl; 

		float topTerm = roughtParameter * roughtParameter * positiveCaracteristic(dot(m, rec.normal));
		float cos0m = dot(m, rec.normal);
		float cos40m = cos0m * cos0m * cos0m * cos0m;
		float tan20m = (1 - cos0m * cos0m) / (cos0m * cos0m);
		float secondBottomTerm = (roughtParameter * roughtParameter + tan20m) * (roughtParameter * roughtParameter + tan20m);
		std::cout << "cos0m" << cos0m << std::endl;
		float bottomTerm = 3.121592 * cos40m * secondBottomTerm;
		float finalTerm = topTerm / bottomTerm;
		std::cout << "first Term : " <<  topTerm << std::endl;
		std::cout << "bottom Term " << bottomTerm << std::endl;
		*/
		if (dot(scattered.direction(), m) > 0.0f && dot(rec.normal , scattered.direction()) > 0.0f)
		{

			
			float woWg = abs(dot(rayIn.direction(), rec.normal));
			float woWm = abs(dot(rayIn.direction(), m));
			float wmWg = abs(dot(m, rec.normal));
			float d = D(m, rec.normal);
			float g = G(rayIn.direction(), scattered.direction(), m, rec.normal);
			Color finalColor = (g  * F* woWm) / (wmWg * woWg  + 1e-8);
			return finalColor;// *abs(dot(rec.normal, unitVector(scattered.direction())));
		}
		else
		{
			return Color(0, 0, 0);
		}
		//return Color(D,D,D);


}

bool CookTorance::isSpecular()
{
	return false;
}



float CookTorance::fresnelApproximation(float ior, float absorbtionCoef , Ray& rayIn, HitRecord& rec , Ray& scattered )
{
	// fresnel approximation for conductor
	Vec3 halfAngle = unitVector(rayIn.direction() + scattered.direction());
	float cosTheta = std::max(0.0f,dot(rayIn.direction(), halfAngle));
	float topTerm = (ior - 1) * (ior - 1) + 4 * ior * pow((1 - cosTheta), 5) + absorbtionCoef*absorbtionCoef;
	float bottomTerm = (ior + 1) * (ior + 1) + absorbtionCoef * absorbtionCoef;
	return topTerm / (bottomTerm +.000001);
}



float CookTorance::positiveCaracteristic(float x)
{
	if (x <= 0)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}

float CookTorance::ggxNormalDistribution(float NdotH, float roughness)
{
	float a2 = roughness * roughness;
	float d = ((NdotH * a2 - NdotH) * NdotH + 1);
	return a2 / (d * d * 3.141592);
}

float CookTorance::schlickMaskingTerm(float NdotL, float NdotV, float roughness)
{
	// Karis notes they use alpha / 2 (or roughness^2 / 2)
	float k = roughness * roughness / 2;

	// Compute G(v) and G(l).  These equations directly from Schlick 1994
	//     (Though note, Schlick's notation is cryptic and confusing.)
	float g_v = NdotV / (NdotV * (1 - k) + k);
	float g_l = NdotL / (NdotL * (1 - k) + k);
	return g_v * g_l;
}

Vec3 CookTorance::getGGXMicrofacet(float roughtness, Vec3 normal)
{


	float e1 = utils::quickRandom();
	float e2 = utils::quickRandom();

	float a2 = roughtParameter * roughtParameter;
	ONB uvw;
	uvw.buildFromW(normal);

	float inclination = atan(roughtParameter * sqrt(e1 / (1.0 - e1))); // ?
	float azimuth = 2.0 * 3.14159265359 * e2; // f
	float x = sin(inclination) * cos(azimuth);
	float y = sin(inclination) * sin(azimuth);
	float z = cos(inclination);
	Vec3 microNormal(x, y, z);
	microNormal = uvw.local(microNormal);
	microNormal.makeUnitVector();
	return microNormal;
}

float CookTorance::G(Vec3 inDirection, Vec3 outDirection, Vec3 m, Vec3 n)
{
	return G1(unitVector(inDirection) , m , n ) * G1(unitVector(outDirection), m, n);
}

float CookTorance::G1(Vec3 v, Vec3 m, Vec3 n)
{
	float firstTerm = positiveCaracteristic(dot(v, m) / dot(v, n));
	float cos0v = dot(unitVector(v), unitVector(n));
	float tan20v = (1 - cos0v * cos0v) / (cos0v * cos0v);

	float secondTerm = 2 / (1 + sqrt((1 + roughtParameter * roughtParameter * tan20v)));
	return firstTerm * secondTerm;
}

float CookTorance::D(Vec3 m, Vec3 n)
{
	float topTerm = roughtParameter * roughtParameter * positiveCaracteristic(dot(m, n));
	float cos0m = dot(m, n);
	float cos40m = cos0m * cos0m * cos0m * cos0m;
	float tan20m = (1 - cos0m * cos0m) / (cos0m * cos0m);
	float secondBottomTerm = (roughtParameter * roughtParameter + tan20m) * (roughtParameter * roughtParameter + tan20m);
	//std::cout << "cos0m" << cos0m << std::endl;
	float bottomTerm = 3.141592 * cos40m * secondBottomTerm ;
	float finalTerm = topTerm / bottomTerm;
	return  finalTerm;
}




Color CookTorance::shlick(float cosine, Color R0)
{
	return R0 + (Color(1, 1, 1) - R0) * powf(1 - cosine, 5);
}
