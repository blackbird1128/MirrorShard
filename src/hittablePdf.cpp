#include "hittablePdf.h"
#include "..\include\hittablePdf.h"

hittablePdf::hittablePdf(HittablePtr obj, Vec3& o)
{
	object = obj;
	origin = o;
}

float hittablePdf::value(Vec3& direction)
{
	return object->pdf(origin , direction);
}

Vec3 hittablePdf::generate()
{
	return object->samplePoint(origin);
}
