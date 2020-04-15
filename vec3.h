#pragma once
#include <cmath>
#include <stdexcept>
#include <ostream>
#include <iostream>
#include <random>

class Vec3
{
public:
	Vec3();
	Vec3(float X, float Y, float Z);
	const float lenght();
	const float squaredLenght();
	inline float operator[](int i);
	Vec3 makeUnitVector();
	Vec3 operator-() const;
	Vec3 operator-=(Vec3 vec2);
	Vec3 operator+=(Vec3 vec2 );
	Vec3 operator*=(float t);
	Vec3 operator*(Vec3 vec2);
	Vec3 operator/(Vec3 vec2);
	

	float x;
	float y;
	float z; 



private:









};

std::ostream& operator<<(std::ostream& os, Vec3 t);
std::istream& operator>>(std::istream& is, Vec3& t);
Vec3 operator+(Vec3 a, Vec3 b);
Vec3 operator-(Vec3 a, Vec3 b);
Vec3 operator*(Vec3 a , float t);
Vec3 operator*(float t, Vec3 vec);
Vec3 operator/(Vec3 a, float t);
Vec3 unitVector(Vec3 a);
float dot(const Vec3& vec1, const Vec3& vec2);
float distance(Vec3	a, Vec3 b);