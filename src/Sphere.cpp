#include "Sphere.h"

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
			return true;

			
		}
		root = (-b + sqrt(discriminant) )/ ( a);
		if (root < tMax && root > tMin)
		{
			rec.t = root;
			rec.p = r.pointAt(root);
			rec.normal = (rec.p - center) / radius;
			rec.mat = mat;
			return true;


		}
	}
	return false;
}
