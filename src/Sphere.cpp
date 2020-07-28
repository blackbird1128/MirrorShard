#include "Sphere.h"
#include "ONB.h"
#include "MathUtils.hpp"
#include <AABB.h>


Sphere::Sphere(Vec3 center, float radius)
{
	this->center = center;
	this->radius = radius;
}

void Sphere::setMaterial(std::shared_ptr<Material> m)
{
	mat = m;
}

bool Sphere::hit(Ray r, float tMin, float tMax, HitRecord& rec)
{
	Vec3 oc = r.origin() - center;
	float a = dot(r.direction(), r.direction());
	float b = dot(oc, r.direction());
	float c = dot(oc, oc) - (radius * radius);
	float discriminant = b * b -  a * c;




	if (discriminant > 0)
	{
		float enterDistance = (-b - sqrt(discriminant)) / (a);
		float exitDistance = (-b + sqrt(discriminant)) / (a);

		Vec3 enterPoint = r.pointAt(enterDistance);
		Vec3 exitPoint = r.pointAt(exitDistance);
		rec.normalisedDistInMat = distance(enterPoint, exitPoint) / (radius * 2);

		float root = (-b - sqrt(discriminant) )/ ( a);
		if (root < tMax && root > tMin)
		{
			rec.t = root;
			rec.p = r.pointAt(root);
			rec.normal = (rec.p - center) / radius;
			rec.mat = mat;
			rec.u = 0.5 + atan2f(rec.normal.x, rec.normal.z)/ 6.28318;
			rec.v = 0.5 - asinf(rec.normal.y) / 3.14159;
			return true;

			
		}
		root = (-b + sqrt(discriminant) )/ ( a);
		if (root < tMax && root > tMin)
		{
			rec.t = root;
			rec.p = r.pointAt(root);
			rec.normal = (rec.p - center) / radius;
			rec.mat = mat;
			rec.u = 0.5 + atan2f(rec.normal.x, rec.normal.z) / 6.28318;
			rec.v = 0.5 - asinf(rec.normal.y) / 3.14159;
			return true;


		}
	}
	return false;
}

float Sphere::pdf(Vec3& origin, Vec3& direction)
{
	HitRecord rec;
	if (!this->hit(Ray(origin, direction), 0.001, std::numeric_limits<float>::max(), rec))
	{
		return 0;
	}

	float cosThetaMax = sqrt(1 - radius * radius / (center - origin).squaredLenght());
	float solidAngle = 2 * 3.14159 * (1 - cosThetaMax);
	return 1 / solidAngle;
}



Vec3 Sphere::samplePoint(Vec3& origin)
{
	Vec3 direction = center - origin;
	auto distance_squared = direction.squaredLenght();
	ONB uvw;
	uvw.buildFromW(direction);
	return uvw.local(utils::randomToSphere(radius, distance_squared));
}

AABB Sphere::getAABB()
{
	return AABB(*this);
}

Vec3 Sphere::getCenter()
{
	return center;
}

float Sphere::getRadius()
{
	return radius;
}
