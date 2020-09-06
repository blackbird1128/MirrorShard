#include "ParameterMap.h"
#include "..\include\ParameterMap.h"

ParameterMap::ParameterMap(Image parameter, float scale) : map(0,0)
{
	map = parameter;
	scaleRate = scale;
}

bool ParameterMap::isEmpty()
{
	if (map.getHeight() == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

float ParameterMap::getParameter(float u, float v)
{
	v = 1.0f - v;
	u = std::clamp(u, 0.0f, 1.0f);
	v = std::clamp(v, 0.0f, 1.0f);
	int i = static_cast<int>(u * (map.getWidth())-1);
	int j = static_cast<int>(v * (map.getHeight())-1);

	return float(map(j, i).r)*scaleRate;
}
