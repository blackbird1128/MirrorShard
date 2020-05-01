#pragma once
#include "Color.h"
#include <vector>
#include <string>
class Image
{

public:
	Image(int y, int x);
	Color& operator()(int y, int x);
	void setPixel(int y ,  int x, Color col);
	void toPpmFile(std::string filename);



private:
	int width;
	int height;
	std::vector<Color> pixels;




};

