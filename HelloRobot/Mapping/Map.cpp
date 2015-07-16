/*
 * Map.cpp
 *
 *  Created on: Jun 16, 2015
 *      Author: colman
 */

#include "Map.h"
#include "pngUtil.h"
#include <vector>

Map::Map() {}

double Map::Map_X_Cm()
{
	return (X_Pixles * Cm_To_Pixel_Ratio);
}

double Map::Map_Y_Cm()
{
	return (Y_Pixles * Cm_To_Pixel_Ratio);
}

unsigned Map::getCellImageColor(unsigned row, unsigned col, const vector<unsigned char>& rawImage, unsigned imageWidth, unsigned imageHeight,
                                     unsigned pixelsPerOneGrid) {
	for (unsigned i = 0; i < pixelsPerOneGrid; i++) {
		for (unsigned j = 0; j < pixelsPerOneGrid; j++) {
			unsigned char color = pngUtil::getPixelColor(rawImage, imageWidth, imageHeight, row * pixelsPerOneGrid + i, col * pixelsPerOneGrid + j);
			if (color == IMAGE_COLOR_OBSTACLE) {
				return IMAGE_COLOR_OBSTACLE;
			}
		}
	}

	return IMAGE_COLOR_CLEAR;
}

