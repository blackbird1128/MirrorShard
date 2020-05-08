#include "Color.h"

Color::Color()
{
	r = 0;
	g = 0;
	b = 0;

}

Color::Color(float red, float green, float blue)
{
	r = red;
	g = green;
	b = blue;

}

Color Color::clamp()
{
	if (r > 1)
	{
		r = 1;
	}
	if (r < 0)
	{
		r = 0;
	}

	if (g > 1)
	{
		g = 1;
	}
	if (g < 0)
	{
		g = 0;
	}

	if (b > 1)
	{
		b = 1;
	}
	if (b < 0)
	{
		b = 0;
	}
	return *this;
}

Color Color::operator+=(Color a)
{
	r += a.r;
	g += a.g;
	b += a.b;
	return *this;
}

Color operator+(Color a, Color b)
{
	return Color(a.r + b.r , a.g + b.g , a.b +	b.b );
}

Color operator-(Color a, Color b)
{
	return Color(a.r - b.r, a.g - b.g, a.b - b.b);
}

Color operator*(Color a, Color b)
{
	return Color(a.r * b.r, a.g * b.g, a.b * b.b);
}

Color operator*(float a, Color b)
{
	return Color(a * b.r , a *b.g , a*b.b );
}

Color operator*(Color a, float b)
{
	return Color(a.r * b , a.g * b , a.b * b);
}

Color operator/(Color a, float b)
{
	return Color(a.r / b, a.g / b, a.b /  b);
}


