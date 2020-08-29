#pragma once
#include "pdf.h"
#include "ONB.h"
#include "MathUtils.hpp"
#include "Ray.h"
class GGXSmithPdf : public pdf
{
public:


	GGXSmithPdf(Vec3 microNormal ,Vec3 normal , Vec3 inDirection  ,float roughtness );
	float G(Vec3 inDirection, Vec3 outDirection, Vec3 m, Vec3 n);
	float G1(Vec3 v, Vec3 m, Vec3 n);
	float positiveCaracteristic(float x);
	float value(Vec3& direction) override;
	Vec3  generate() override;
private:
	float a;
	Ray incomingRay;
	ONB uvw;
	Vec3 m;
	Vec3 n;
	Vec3 inDir;
	Vec3 outDir;
};

