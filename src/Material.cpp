#include "Material.h"
#include <random>
#include <cmath>



Vec3 reflect(const Vec3& v, const Vec3& unitV)
{
		return v - 2 * dot(v, unitV) * unitV;

}





