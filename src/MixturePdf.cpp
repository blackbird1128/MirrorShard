#include "MixturePdf.h"
#include "MathUtils.hpp"
#include "..\include\MixturePdf.h"

MixturePdf::MixturePdf(std::vector<pdfPtr> pdfList)
{
	for(int i = 0 ; i < pdfList.size(); i++)
	{
		pdfMix.push_back(std::move(pdfList[i]));
	
	}
}

float MixturePdf::value(Vec3& direction)
{
	float weight = 1.0 / pdfMix.size();
	float sum = 0;
	for (const auto& pdf : pdfMix)
	{
		sum += weight * pdf->value(direction);
	}
	return sum;
}

Vec3 MixturePdf::generate()
{
	return pdfMix[utils::randomInt(0,pdfMix.size()-1)]->generate();
}
