#include "Image.h"
#include <fstream>
Image::Image(int y, int x)
{
	height = y;
	width = x;
	for (int i = 0; i < y * x; i++)
	{

		pixels.push_back(Color(0, 0, 0));
	}

}

Color& Image::operator()(int y, int x)
{
	return pixels[y * width + x ];
}

void Image::setPixel(int y, int x, Color col)
{
	pixels[y * width + x] = col;
}

void Image::toPpmFile(std::string filename)
{
	std::ofstream ppmWriter;
	ppmWriter.open(filename);
	ppmWriter << "P3\n" << width << " " << height << "\n255\n";
	for (int i = pixels.size() ; i >= 0 ; i--)
	{
		int ir = int(255.99 * pixels[i].r);
		int ig = int(255.99 * pixels[i].g);
		int ib = int(255.99 * pixels[i].b);

		ppmWriter << ir << " " << ig << " " << ib << "\n";


	}
}
