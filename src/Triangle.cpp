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
	rec.u = vertex0uv.x * thirdBaryCoord + vertex1uv.x * firstBaryCoord + vertex2uv.x * secondBaryCoord; 
	rec.v = vertex0uv.y * thirdBaryCoord + vertex1uv.y * firstBaryCoord + vertex2uv.y * secondBaryCoord;
	rec.normal = (vertex0Normal * thirdBaryCoord + vertex1Normal * firstBaryCoord + vertex2Normal * secondBaryCoord).makeUnitVector();
	rec.p = r.pointAt(hitDist);
	rec.p = rec.p + 0.00001 * rec.normal;
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

AABB Triangle::getAABB()
{
	return AABB(*this);
}

Vec3 Triangle::getCenter()
{
	float xCenter = (vertex0.x + vertex1.x + vertex2.x) / 3;
	float yCenter = (vertex0.y + vertex1.y + vertex2.y) / 3;
	float zCenter = (vertex0.z + vertex1.z + vertex2.z) / 3;
	return Vec3(xCenter , yCenter , zCenter);
}

bool operator==(Triangle t1, Triangle t2)
{
	if (t1.vertex0 == t2.vertex0 && t1.vertex1 == t2.vertex1 && t1.vertex2 == t2.vertex2)
	{
		return true;
	}
	return false;
}
