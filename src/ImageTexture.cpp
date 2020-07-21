#include "ImageTexture.h"
#include <algorithm>


Color ImageTexture::getColor(double u, double v)
{
	v = 1.0 - v;
	u = std::clamp(u, 0.0, 1.0);
	v = std::clamp(v, 0.0, 1.0);
	int i = static_cast<int>(u * (textureImage.getWidth()));
	int j = static_cast<int>(v * (textureImage.getHeight()));
	return textureImage(j  ,i );
}
