#include "ColorTexture.h"

ColorTexture::ColorTexture(Color texColor)
{
	textureColor = texColor;
}

ColorTexture::ColorTexture(float r, float g, float b)
{
	textureColor = Color(r, g, b);
}

Color ColorTexture::getColor(double u, double v)
{
	return textureColor;
}
