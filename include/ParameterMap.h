#pragma once
#include "Image.h"
class ParameterMap
{
public:

	ParameterMap() : map(0, 0), scaleRate{1}{};
	ParameterMap(Image parameter, float scale);
	bool isEmpty();
	float getParameter(float u, float v);

private:

	Image map;
	float scaleRate;



};

