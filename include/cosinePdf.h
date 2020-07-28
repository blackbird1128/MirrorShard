#pragma once
#include "pdf.h"
#include "ONB.h"
class cosinePdf : public pdf
{
public:
	cosinePdf(Vec3 w) { uvw.buildFromW(w); }
	float value(Vec3& direction) override;
	Vec3  generate() override;

private:
	ONB uvw;

};

