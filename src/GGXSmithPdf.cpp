#include "GGXSmithPdf.h"
#include "Material.h"

GGXSmithPdf::GGXSmithPdf(Vec3 microNormal, Vec3 normal, Vec3 inDirection, float roughtness)
{

	inDir = inDirection;
	m = microNormal;
	n = normal;
	a = roughtness;
}

float GGXSmithPdf::G(Vec3 inDirection, Vec3 outDirection, Vec3 m, Vec3 n)
{
	return G1(unitVector(inDirection), m, n) * G1(unitVector(outDirection), m, n);
}

float GGXSmithPdf::G1(Vec3 v, Vec3 m, Vec3 n)
{
	return 1.0;
	float firstTerm = positiveCaracteristic(dot(v, m) / dot(v, n));
	float cos0v = dot(unitVector(v), unitVector(n));
	float tan20v = (1 - cos0v * cos0v) / (cos0v * cos0v);

	float secondTerm = 2 / (1 + sqrt((1 + a * a * tan20v)));
	return firstTerm * secondTerm;

}



float GGXSmithPdf::positiveCaracteristic(float x)
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



float GGXSmithPdf::value(Vec3& direction)
{
	return 1.0;
	
	float absIdotm = abs(dot(inDir, m));
	Vec3 reflected = unitVector(reflect(unitVector(inDir), unitVector(m)));
	//std::cout << "reflected 1 " << reflected << std::endl;
	//std::cout  << "new formula : " << 2.0 * absIdotm * m - inDir << std::endl; 


	float Gvalue = G(inDir, reflected, m, n);

	float bottomTerm = abs(dot(inDir, n)) * abs(dot(m, n));
	return  (absIdotm * Gvalue)/ (bottomTerm + 1e-5);
}

Vec3 GGXSmithPdf::generate()
{
	return unitVector(reflect(unitVector(inDir), unitVector(m)));
	float absIdotm = abs(dot(inDir, m));
 	return 2.0 * absIdotm * m - inDir;;
}
