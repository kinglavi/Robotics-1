/*
 * pngUtil.cpp
 *
 *  Created on: Mar 30, 2015
 *      Author: colman
 */
#include "pngUtil.h"
#include "loadpng.h"
#include <iostream>


//Encode from raw pixels to disk with a single function call
//The image argument has width * height RGBA pixels or width * height * 4 bytes
void encodeOneStep(const char* filename, std::vector<unsigned char> image,
		unsigned width, unsigned height) {
	//Encode the image
	unsigned error = lodepng::encode(filename, image, width, height);

	//if there's an error, display it
	if (error)
		std::cout << "encoder error " << error << ": "
				<< lodepng_error_text(error) << std::endl;
}

void decodeOneStep(const char* filename) {
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
void ConvertMapBlackToWhiteAndWhiteToBlack(const char* filename, int paddingSize) {
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
	navImage.resize(width * height * 4);
	paddedImage.resize(width * height * 4);
	unsigned char color;


	for (y = 0; y < height; y++)
		for (x = 0; x < width; x++) {
//			if (image[y * width * 4 + x * 4 + 0]
//					|| image[((y + paddingSize) * (width + paddingSize*2) * 4) + (x + (paddingSize) * 4 + 1)]
//					|| image[(y + paddingSize) * (width + paddingSize*2) * 4 + (x+paddingSize) * 4 + 2])
//				color = 0;
//			else
//				color = 255;
			if (!image[y * width * 4 + x * 4 + 0] && !image[y * width * 4 + x * 4 + 1] && !image[y * width * 4 + x * 4 + 2])
			{

				for (innerX = x; innerX <= x +(paddingSize*2); innerX++)
				{
					for (innerY = y ; innerY <= y + (paddingSize*2); innerY++)
					{
						paddedImage[((innerY + paddingSize) * (width + paddingSize*2) * 4) + (innerX + (paddingSize) * 4 + 0)] = 0;
						paddedImage[((innerY + paddingSize) * (width + paddingSize*2) * 4) + (innerX + (paddingSize) * 4 + 1)] = 0;
						paddedImage[((innerY + paddingSize) * (width + paddingSize*2) * 4) + (innerX + (paddingSize) * 4 + 2)] = 0;
						paddedImage[((innerY + paddingSize) * (width + paddingSize*2) * 4) + (innerX + (paddingSize) * 4 + 3)] = 255;
					}
				}

			}

			navImage[y * width * 4 + x * 4 + 0] = color;
			navImage[y * width * 4 + x * 4 + 1] = color;
			navImage[y * width * 4 + x * 4 + 2] = color;
			navImage[y * width * 4 + x * 4 + 3] = 255;
		}



	encodeOneStep("/usr/robotics/PcBotWorld/newMap.png", navImage, width, height);
}
