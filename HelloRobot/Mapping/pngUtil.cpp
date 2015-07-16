/*
 * pngUtil.cpp
 *
 *  Created on: Mar 30, 2015
 *      Author: colman
 */
#include "pngUtil.h"
#include "loadpng.h"

//Encode from raw pixels to disk with a single function call
//The image argument has width * height RGBA pixels or width * height * 4 bytes
void pngUtil::encodeOneStep(const char* filename, std::vector<unsigned char> image,
		unsigned width, unsigned height) {
	//Encode the image
	unsigned error = lodepng::encode(filename, image, width, height);

	//if there's an error, display it
	if (error)
		std::cout << "encoder error " << error << ": "
				<< lodepng_error_text(error) << std::endl;
}

void pngUtil::decodeOneStep(const char* filename) {
	std::vector<unsigned char> image; //the raw pixels
	unsigned width, height;

	//decode
	unsigned error = lodepng::decode(image, width, height, filename);

	//if there's an error, display it
	if (error)
		std::cout << "decoder error " << error << ": "
				<< lodepng_error_text(error) << std::endl;

	//the pixels are now in the vector "image", 4 bytes per pixel, ordered RGBARGBA..., use it as texture, draw it, ...
}
void pngUtil::PadMap(const char* filename, unsigned paddingSize) {
	std::vector<unsigned char> image; //the raw pixels
	unsigned width, height, paddedWidth, paddedHeight;
	unsigned x, y, innerX, innerY;
	//decode
	unsigned error = lodepng::decode(image, width, height, filename);

	//if there's an error, display it
	if (error)
		std::cout << "decoder error " << error << ": "
				<< lodepng_error_text(error) << std::endl;

	std::vector<unsigned char> navImage; //the raw pixels
	std::vector<unsigned char> paddedImage;

	paddedWidth = width + (paddingSize * 2);
	paddedHeight = height + (paddingSize * 2);
	paddedImage.resize(paddedWidth * paddedHeight * 4);
	unsigned char color;

	for (y = 0; y < paddedHeight; y++)
		for (x = 0; x < paddedWidth; x++)
		{
			paddedImage[y * (paddedWidth * 4) + (x * 4 + 0)] = 255;
			paddedImage[y * (paddedWidth * 4) + (x * 4 + 1)] = 255;
			paddedImage[y * (paddedWidth * 4) + (x * 4 + 2)] = 255;
			paddedImage[y * (paddedWidth * 4) + (x * 4 + 3)] = 255;
		}



	for (y = 0; y < height; y++)
		for (x = 0; x < width; x++) {
//			if (image[y * width * 4 + x * 4 + 0]
//					|| image[((y + paddingSize) * (width + paddingSize*2) * 4) + (x + (paddingSize) * 4 + 1)]
//					|| image[(y + paddingSize) * (width + paddingSize*2) * 4 + (x+paddingSize) * 4 + 2])
//				color = 0;
//			else
//				color = 255;
			if (image[y * width * 4 + x * 4 + 0] == 0 && image[y * width * 4 + x * 4 + 1] == 0 && image[y * width * 4 + x * 4 + 2] == 0)
			{

				for (innerX = x; innerX <= x +(paddingSize*2); innerX++)
				{
					for (innerY = y ; innerY <= y + (paddingSize*2); innerY++)
					{
						paddedImage[innerY * (paddedWidth * 4) + (innerX * 4 + 0)] = 0;
						paddedImage[innerY * (paddedWidth * 4) + (innerX * 4 + 1)] = 0;
						paddedImage[innerY * (paddedWidth * 4) + (innerX * 4 + 2)] = 0;
						paddedImage[innerY * (paddedWidth * 4) + (innerX * 4 + 3)] = 255;
					}
				}

			}
		}

	encodeOneStep("/usr/robotics/PcBotWorld/newMap.png", paddedImage, paddedWidth, paddedHeight);
}

void pngUtil::CreateGrid(const char* filename, unsigned paddingSize, int MapResolutionCM, int GridResolutionCM)
{
	PadMap(filename, paddingSize);
	double PixelsToCell = GridResolutionCM/MapResolutionCM;
	unsigned width, height;

	std::vector<unsigned char> image;

	unsigned error = lodepng::decode(image, width, height, filename);

	int gridHeight = height/PixelsToCell;
	int gridWidth = width/PixelsToCell;

	unsigned char map [gridHeight][gridHeight];

	unsigned x, y;

	for (x = 0; x < height; x+=PixelsToCell)
			for (y = 0; y < width; y+=PixelsToCell)
			{
				image[y * (width * 4) + (x * 4 + 0)] = 255;
				image[y * (width * 4) + (x * 4 + 1)] = 255;
				image[y * (width * 4) + (x * 4 + 2)] = 255;
				image[y * (width * 4) + (x * 4 + 3)] = 255;
			}

}

unsigned char pngUtil::getPixelColor(const std::vector<unsigned char>& rawImage, unsigned width, unsigned height, unsigned row, unsigned col) {
	unsigned basePos = row * width * 4 + col * 4;

	if (width == 0 || height == 0 || basePos + A_OFFSET > rawImage.size()) {
		return COLOR_INVALID;
	}

	if (rawImage[basePos + R_OFFSET] == COLOR_BLACK && rawImage[basePos + G_OFFSET] == COLOR_BLACK && rawImage[basePos + B_OFFSET] == COLOR_BLACK) {
		return COLOR_BLACK;
	}
	return COLOR_WHITE;
}
