#include "CookTorance.h"
#include "MathUtils.hpp"
#include "GGXSmithPdf.h"
#include "ONB.h"
#include "cosinePdf.h"

CookTorance::CookTorance(float roughness, Vec3 ior, Vec3 kIor, std::shared_ptr<Texture> tex)
{
	roughtParameter = roughness;
	matIor = ior;
	matIorAbsorbtion = kIor;
	matTexture = tex;
}

CookTorance::CookTorance(ParameterMap roughness, Vec3 ior, Vec3 kIor, std::shared_ptr<Texture> tex)
{
	roughtParameter = 1.0;
	roughtnessMap = roughness;
	matIor = ior;
	matIorAbsorbtion = kIor;
	matTexture = tex;
}

bool CookTorance::scatter(Ray& rayIn, HitRecord& rec, scatterRecord& scatterRec, Ray& scattered)
{



	float iterationRoughness = roughtParameter;

	if (!roughtnessMap.isEmpty())
	{

		iterationRoughness = roughtnessMap.getParameter(rec.u, rec.v);
		//std::cout << "iteration roughness : " << iterationRoughness << std::endl;
	}
	

	 m = getGGXMicrofacet(iterationRoughness , rec.normal );
	 Vec3 reflected = unitVector(reflect(unitVector(rayIn.direction()), unitVector(m)));
	 scatterRec.specular_ray = Ray(rec.p, reflected);
	 scattered = scatterRec.specular_ray;
	//scatterRec.attenuation = Color(1.0,1.0,1.0);
	Color F(fresnelApproximation(matIor.x, matIorAbsorbtion.x, rayIn, rec, scattered), fresnelApproximation(matIor.y, matIorAbsorbtion.y, rayIn, rec, scattered), fresnelApproximation(matIor.z, matIorAbsorbtion.z, rayIn, rec, scattered));
	//F =  shlick(dot(rayIn.direction(), m), Color(0.7, 0.7, 0.7));

	if (dot(scattered.direction(), m) > 0.0f && dot(rec.normal, scattered.direction()) > 0.0f)
	{


		float woWg = abs(dot(rayIn.direction(), rec.normal));
		float woWm = abs(dot(rayIn.direction(), m));
		float wmWg = abs(dot(m, rec.normal));
		//float d = D(m, rec.normal);
		float g = G(rayIn.direction(), scattered.direction(), m, rec.normal, iterationRoughness);
		Color finalColor = (g * F * woWm) / (std::max(wmWg * woWg, 0.00001f));
		scatterRec.attenuation =  finalColor;// *abs(dot(rec.normal, unitVector(scattered.direction())));
	}
	else
	{
		scatterRec.attenuation =  Color(0, 0, 0);
	}

	//std::unique_ptr<GGXSmithPdf> GGXpdf = std::make_unique<GGXSmithPdf>(m, rec.normal, rayIn.direction()  , roughtParameter);


	scatterRec.pdfPointer = nullptr;

	return (dot(scatterRec.specular_ray.direction(),m ) > 0);
}

Color CookTorance::scatteringPdf(Ray& rayIn, HitRecord& rec, Ray& scattered)
{

		/*
		Color F(fresnelApproximation(matIor.x, matIorAbsorbtion.x, rayIn, rec, scattered), fresnelApproximation(matIor.y, matIorAbsorbtion.y, rayIn, rec, scattered), fresnelApproximation(matIor.z, matIorAbsorbtion.z, rayIn, rec, scattered));


		if (dot(scattered.direction(), m) > 0.0f && dot(rec.normal , scattered.direction()) > 0.0f)
		{

			
			float woWg = abs(dot(rayIn.direction(), rec.normal));
			float woWm = abs(dot(rayIn.direction(), m));
			float wmWg = abs(dot(m, rec.normal));
			float d = D(m, rec.normal);
			float g = G(rayIn.direction(), scattered.direction(), m, rec.normal,roughtParameter);
			Color finalColor =(g  * F* woWm) / ( std::max(wmWg * woWg  , 0.00001f));
			return finalColor;// *abs(dot(rec.normal, unitVector(scattered.direction())));
		}
		else
		{
			return Color(0, 0, 0);
		}
		*/
	return Color(0, 0, 0);
		//return Color(D,D,D);


}

bool CookTorance::isSpecular()
{
	return true;
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



Vec3 CookTorance::getGGXMicrofacet(float roughtness, Vec3 normal)
{


	float e1 = utils::quickRandom();
	float e2 = utils::quickRandom();

	float a2 = roughtness * roughtness;
	ONB uvw;
	uvw.buildFromW(normal);

	float inclination = atan(roughtness * sqrt(e1 / (1.0 - e1))); // ?
	float azimuth = 2.0 * 3.14159265359 * e2; // f
	float x = sin(inclination) * cos(azimuth);
	float y = sin(inclination) * sin(azimuth);
	float z = cos(inclination);
	Vec3 microNormal(x, y, z);
	microNormal = uvw.local(microNormal);
	microNormal.makeUnitVector();
	return microNormal;
}

float CookTorance::G(Vec3 inDirection, Vec3 outDirection, Vec3 m, Vec3 n,float roughness)
{
	return G1(unitVector(inDirection) , m , n , roughness) * G1(unitVector(outDirection), m, n , roughness);
}

float CookTorance::G1(Vec3 v, Vec3 m, Vec3 n,float  roughness)
{
	float firstTerm = positiveCaracteristic(dot(v, m) / dot(v, n));
	float cos0v = dot(unitVector(v), unitVector(n));
	float tan20v = (1 - cos0v * cos0v) / (cos0v * cos0v);

	float secondTerm = 2 / (1 + sqrt((1 + roughness * roughness * tan20v)));
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
