#include "vec3.h"



Vec3::Vec3()
{
	
	x = 0;
	y = 0;
	z = 0;
}

Vec3::Vec3(float X, float Y, float Z)
{	
	x = X;
	y = Y;
	z = Z;

}

const float Vec3::lenght()
{
	return sqrt(x*x + y*y + z*z);
}

const float Vec3::squaredLenght()
{
	return x*x + y*y + z*z;
}

inline float Vec3::operator[](int i)
{
	if (i == 0)
	{
		return x;
	}
	if (i == 1)
	{
		return y;
	}
	if (i == 2)
	{
		return z;
	}
	throw std::out_of_range("out of range (index : 0:x , 1:y , 2:z)");

}

Vec3 Vec3::makeUnitVector()
{
	return *this*(1/ (this->lenght() ) );
}

Vec3 Vec3::operator-() const
{
	return Vec3(-x,-y,-z);
}

Vec3 Vec3::operator-=(Vec3 vec2)
{
	x -= vec2.x;
	y -= vec2.y;
	z += vec2.z;
	return *this;
}

Vec3 Vec3::operator+=(Vec3 vec2)
{
	x += vec2.x;
	y += vec2.y;
	z += vec2.z;
	return *this;
}

Vec3 Vec3::operator*=(float t)
{
	x *= t;
	y *= t;
	z *= t;
	return *this;
}

Vec3 Vec3::operator*(Vec3 vec2)
{
	return Vec3(x * vec2.x, y * vec2.y, z * vec2.z);
}

Vec3 Vec3::operator/(Vec3 vec2)
{
	return Vec3(x / vec2.x, y / vec2.y , z/vec2.z);
}

std::ostream& operator<<(std::ostream& os, Vec3 t)
{
	os << t.x << " " << t.y << " " << t.z;
	return os;
}

std::istream& operator>>(std::istream& is, Vec3& t)
{
	is >> t.x >> t.y >> t.z;
	return is;
}

Vec3 operator+(Vec3 a, Vec3 b)
{
	return Vec3(a.x + b.x , a.y + b.y , a.z + b.z );
}

Vec3 operator-(Vec3 a, Vec3 b)
{
	return Vec3(a.x - b.x , a.y -b.y , a.z -b.z);
}

Vec3 operator*(Vec3 a, float t)
{
	return a*= t;
}

Vec3 operator*(float t, Vec3 vec)
{
	return Vec3(t*vec.x , t*vec.y , t*vec.z);
}

Vec3 operator/(Vec3 a, float t)
{
	return a*(1.0/t);
}

Vec3 unitVector(Vec3 a)
{
	return  a / a.lenght();
}



float dot(const Vec3& vec1, const Vec3& vec2)
{
	return vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z;
}

float distance(Vec3 a, Vec3 b)
{
	return sqrt((b.x - a.x) * (b.x - a.x) + (b.y - a.y) * (b.y - a.y) + (b.z - a.z) * (b.z - a.z));
}
