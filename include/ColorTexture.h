#pragma once
#include "Texture.h"
class ColorTexture : public Texture
{

public:
	ColorTexture(Color texColor);
	ColorTexture(float r, float g, float b);
	Color getColor(double u, double v);

private:
	Color textureColor;
};

