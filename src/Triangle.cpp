#include "Triangle.h"

Triangle::Triangle(Vec3 vert0, Vec3 vert1, Vec3 vert2)
{
	vertex0 = vert0;
	vertex1 = vert1;
	vert2 = vert2;
}

bool Triangle::hit(Ray r, float tMin, float tMax, HitRecord& rec) // https://fr.wikipedia.org/wiki/Algorithme_d%27intersection_de_M%C3%B6ller%E2%80%93Trumbore
{
	float epsilon = 0.0000001;
	float a, f, u, v;
	Vec3 direction = r.direction();
	Vec3 edge1 = vertex1 - vertex0;
	Vec3 edge2 = vertex2 - vertex0;
	Vec3 normal = edge1.crossProduct(edge2);
	Vec3 pVec = direction.crossProduct(edge2);
	float det = dot(edge1, pVec);
	if(fabs(det) < epsilon)
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
	Vec3 qVec = invPlaneDir.crossProduct(edge1);
	float secondBaryCoord = dot(qVec, direction) * invDet;
	if (secondBaryCoord < 0.f || firstBaryCoord + secondBaryCoord > 1.f)
	{
		return false;
	}
	float hitDist = dot(edge2, qVec) * invDet;
	if (hitDist <= 0.f)
	{
		return false;
	}

		rec.mat = mat;
		//std::cout << "ray origin :" << r.origin() << " direction " << r.direction() << "\n";
		//std::cout << "t:" << hitDist << std::endl;
		//std::cout << r.pointAt(hitDist) << "\n";
		
		rec.t = hitDist;
		rec.normal = (dot(normal , direction) > 0.f ? -normal : normal);
		rec.p = r.pointAt(hitDist);
		return true;


}

void Triangle::setMaterial(std::shared_ptr<Material> m)
{
	mat = m;
}
