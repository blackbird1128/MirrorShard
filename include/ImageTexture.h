#pragma once
#include "Texture.h"
#include "Image.h"
class ImageTexture :
public Texture
{
public:
	ImageTexture() = delete;
	ImageTexture(std::string texturePath) : textureImage(0, 0) { textureImage.loadFromFile(texturePath); };
	Color getColor(double u, double v );

private:
	Image textureImage;

};

