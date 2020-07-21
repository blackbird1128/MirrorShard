#pragma once
#include "Color.h"
#include <vector>
#include <string>
#include <filesystem>
#include <algorithm>

class Image
{

public:
	Image() = delete;
	explicit Image(int y, int x);
	Color& operator()(int y, int x);
	void setPixel(int y ,  int x, Color col);
	int loadFromFile(std::filesystem::path filepath);
	void reversePixels();
	void toPpmFile(std::string filename);
	void toPngFile(std::string filename);
	int getWidth();
	int getHeight();
	Color rawDataAt(std::size_t index);



private:
	int width;
	int height;
	std::vector<Color> pixels;




};

