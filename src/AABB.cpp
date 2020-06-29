#include "AABB.h"
#include "Triangle.h"
#include "Sphere.h"
#include "Ray.h"
#include <algorithm>
#define NOMINMAX

AABB::AABB(Vec3& maxP, Vec3& minP)
{
	pMax = maxP;
	pMin = minP;
}

AABB::AABB(Triangle tr)
{
	pMax.z = std::max(tr.vertex0.z, std::max(tr.vertex1.z, tr.vertex2.z));
	pMax.y = std::max(tr.vertex0.y, std::max(tr.vertex1.y, tr.vertex2.y));
	pMax.x = std::max(tr.vertex0.x, std::max(tr.vertex1.x, tr.vertex2.x));

	pMin.z = std::min(tr.vertex0.z, std::min(tr.vertex1.z, tr.vertex2.z));
	pMin.y = std::min(tr.vertex0.y, std::min(tr.vertex1.y, tr.vertex2.y));
	pMin.x = std::min(tr.vertex0.x, std::min(tr.vertex1.x, tr.vertex2.x));
}

AABB::AABB(Sphere sp)
{
	pMin.x = sp.getCenter().x - sp.getRadius();
	pMin.y = sp.getCenter().y - sp.getRadius();
	pMin.z = sp.getCenter().z - sp.getRadius();


	pMax.x = sp.getCenter().x + sp.getRadius();
	pMax.y = sp.getCenter().y + sp.getRadius();
	pMax.z = sp.getCenter().z + sp.getRadius();

}

bool AABB::hit(Ray r)
{
	Vec3 dirFrac;
	dirFrac.x = 1.0f / r.direction().x;
	dirFrac.y = 1.0f / r.direction().y;
	dirFrac.z = 1.0f / r.direction().z;
	float t1 = (pMin.x - r.origin().x) * dirFrac.x;
	float t2 = (pMax.x - r.origin().x) * dirFrac.x;

	float t3 = (pMin.y - r.origin().y) * dirFrac.y;
	float t4 = (pMax.y - r.origin().y) * dirFrac.y;

	float t5 = (pMin.z - r.origin().z) * dirFrac.z;
	float t6 = (pMax.z- r.origin().z) * dirFrac.z;

	float tmin = std::max( std::max( std::min(t1, t2), std::min(t3, t4))  , std::min(t5, t6) );
	float tmax = std::min( std::min( std::max(t1, t2), std::max(t3, t4) ) , std::max(t5, t6) );
	
	if (tmax < 0)
	{
		return false;
	}
	if (tmin > tmax)
	{
		return false;
	}

	return true;
}

void AABB::expand(AABB box)
{
	pMax.x = std::max(pMax.x, box.pMax.x);
	pMax.y = std::max(pMax.y, box.pMax.y);
	pMax.z = std::max(pMax.z, box.pMax.z);

	pMin.x = std::min(pMin.x, box.pMin.x);
	pMin.y = std::min(pMin.y, box.pMin.y);
	pMin.z = std::min(pMin.z, box.pMin.z);
}

int AABB::longestAxis()
{
	float xDist = std::abs(pMax.x - pMin.x);
	float yDist = std::abs(pMax.y - pMin.y);
	float zDist = std::abs(pMax.z - pMin.z);
	float maxDist =  std::max(xDist, std::max(yDist, zDist));
	if (maxDist == xDist)
	{
		return 0;
	}
	if (maxDist == yDist)
	{
		return 1;
	}
	if (maxDist == zDist)
	{
		return 2;
	}
}
