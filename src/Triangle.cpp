#include "Triangle.h"
#include <limits>
Triangle::Triangle(Vec3 vert0, Vec3 vert1, Vec3 vert2)
{
	vertex0 = vert0;
	vertex1 = vert1;
	vertex2 = vert2;
	edge1 = vertex1 - vertex0;
	edge2 = vertex2 - vertex0;
}

bool Triangle::hit(Ray r, float tMin, float tMax, HitRecord& rec) // https://fr.wikipedia.org/wiki/Algorithme_d%27intersection_de_M%C3%B6ller%E2%80%93Trumbore
{
	constexpr float epsilon = 0.000001;
	Vec3 direction = r.direction();
	Vec3 pVec = direction.crossProduct(edge2);
	const float det = dot(edge1, pVec);
	if(det < epsilon)
	{
		return false;
	}

	float invDet = 1.0 / det;
	Vec3 invPlaneDir = r.origin() - vertex0;
	float firstBaryCoord = dot(invPlaneDir, pVec) * invDet;
	if (firstBaryCoord < 0.f || firstBaryCoord > 1.f)
	{
		return false;
	}
	const Vec3 qVec = invPlaneDir.crossProduct(edge1);
	float secondBaryCoord = dot(qVec, direction) * invDet;
	if (secondBaryCoord < 0.f || firstBaryCoord + secondBaryCoord > 1.f)
	{
		return false;
	}
	float hitDist = dot(edge2, qVec) * invDet;
	if (hitDist <= epsilon)
	{
		return false;
	}
	if (hitDist >= tMax || hitDist < tMin)
	{
		return false;
	}
	const float thirdBaryCoord = 1 - (firstBaryCoord + secondBaryCoord);
	rec.mat = mat;
	rec.t = hitDist;
	rec.normal = (vertex0Normal * thirdBaryCoord + vertex1Normal * firstBaryCoord + vertex2Normal * secondBaryCoord).makeUnitVector();
	rec.p = r.pointAt(hitDist);
	return true;


}

void Triangle::setMaterial(std::shared_ptr<Material> m)
{
	mat = m;
}

void Triangle::computeEdges()
{
	edge1 = vertex1 - vertex0;
	edge2 = vertex2 - vertex0;
}
