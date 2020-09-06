#include "Image.h"
#include "lodepng.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <fstream>
#include <iostream>



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

int Image::loadFromFile(std::filesystem::path filepath)
{
	stbi_ldr_to_hdr_gamma(1.0f);

	//stbi_set_flip_vertically_on_load(true);

	int components;

	float *imageData = stbi_loadf(filepath.string().c_str(),
		&width, &height, &components, 3);
	for (auto i = 0  ; i <height; i++)
	{
		for (auto j = 0; j < width; j++)
		{

			unsigned bytePerPixel = 3;
			float* pixelOffset = imageData + (j + width * i) * bytePerPixel;
			float r = pixelOffset[0];
			float g = pixelOffset[1];
			float b = pixelOffset[2];
			pixels.push_back(Color(r, g, b));
		}
	}
	stbi_image_free(imageData);
	//reversePixels();
	std::vector<unsigned char> data;

	/*
	unsigned int imWidth, imHeight;
	if (filepath.extension() == ".png")
	{
		unsigned error = lodepng::decode(data, imWidth, imHeight, filepath.string());
		std::cout << "width : " << imWidth << std::endl;
		std::cout << "height : " << imHeight << std::endl;
		width = imWidth;
		height = imHeight;
		if (error)
		{
			std::cout << "decoder error " << error << ": " << lodepng_error_text(error) << std::endl;
			return -1;

		}
	}
	else
	{
		std::cout << "[ERROR] : unsuported format " << std::endl;
		return -1;
	}
	pixels.clear();
	float invVal = 1.0 / 255.0;
	for (int i = 0; i < data.size() - 3 ; i+=4)
	{
		pixels.push_back(Color(data[i]*invVal, data[i +1 ]*invVal , data[i + 2 ]*invVal ));
		
	}
	*/
	return 0;
}

void Image::reversePixels()
{
	std::reverse(pixels.begin(), pixels.end());
}

void Image::toPngFile(std::string filename)
{
	std::vector<unsigned char> data;
	for (int i = 0 ; i < pixels.size(); i++)
	{
		data.push_back(static_cast<int>(pixels[i].r * 255.99 ));
		data.push_back(static_cast<int>(pixels[i].g * 255.99));
		data.push_back(static_cast<int>(pixels[i].b * 255.99));
		data.push_back(255);
	}
	unsigned error = lodepng::encode(filename, data, width, height);
	if(error)
	{
		std::cout << "encoder error " << error << ": " << lodepng_error_text(error) << std::endl;
	}

}

int Image::getWidth()
{
	return width;
}

int Image::getHeight()
{
	return height;
}

Color Image::rawDataAt(std::size_t index)
{
	return pixels[index];
}

void Image::toPpmFile(std::string filename)
{
	std::ofstream ppmWriter;
	ppmWriter.open(filename);
	ppmWriter << "P3\n" << width << " " << height << "\n255\n";
	for (int i = 0 ; i < pixels.size(); i++)
	{
		int ir = int(255.99 * pixels[i].r);
		int ig = int(255.99 * pixels[i].g);
		int ib = int(255.99 * pixels[i].b);

		ppmWriter << ir << " " << ig << " " << ib << "\n";
	}
}
