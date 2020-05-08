#pragma once
class Color
{
public:
	Color();
	Color(float r, float g, float b); // color in [0,1] range
	Color clamp();

	Color operator+=(Color a);

	float r, g, b;

};



Color operator+(Color a, Color b);
Color operator-(Color a, Color b);
Color operator*(Color a, Color b);
Color operator*(float a , Color b);
Color operator*(Color a, float b);
Color operator/(Color a, float b);