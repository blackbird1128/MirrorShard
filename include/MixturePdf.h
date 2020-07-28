#pragma once
#include "pdf.h"
#include <memory>
#include <vector>

using pdfPtr = std::unique_ptr<pdf>;

class MixturePdf : public pdf
{
public:
	MixturePdf(std::vector<pdfPtr> pdfList);
	float value(Vec3& direction) override;
	Vec3 generate() override;

private:
	std::vector<pdfPtr> pdfMix;
};

