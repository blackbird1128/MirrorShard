#pragma once
#include "pdf.h"
#include "Hitable.h"
class hittablePdf : public pdf
{
public:
	hittablePdf(HittablePtr obj , Vec3& o);
	float value(Vec3& direction) override;
	Vec3 generate() override;
	void setOrigin(Vec3 newOrigin);

public:
	HittablePtr object;
	Vec3 origin;
};

