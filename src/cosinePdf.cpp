#include "cosinePdf.h"
#include "MathUtils.hpp"

float cosinePdf::value(Vec3& direction)
{
	float cosine = dot(unitVector(direction), uvw.w());
	return (cosine <= 0) ? 0 : cosine / 3.14159265359;
}

Vec3 cosinePdf::generate()
{
	return uvw.local(utils::randomCosineDirection());
}



