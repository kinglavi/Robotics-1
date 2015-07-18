/*
 * Map.cpp
 *
 *  Created on: Jun 16, 2015
 *      Author: colman
 */

#include <vector>

#include "../Mapping/Cell.h"
#include "pngUtil.h"
#include "Map.h"

using namespace Mapping;

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

void Map::CreateGrid(unsigned paddingSize, int MapResolutionCM, int GridResolutionCM)
{

	char* filename = pngUtil::PadMap(filename, paddingSize);
	double PixelsToCell = GridResolutionCM/MapResolutionCM;
	unsigned width, height;

	std::vector<unsigned char> image;

	unsigned error = lodepng::decode(image, width, height, filename);

	int gridHeight = height/PixelsToCell;
	int gridWidth = width/PixelsToCell;

	unsigned char map [gridHeight][gridWidth];

	unsigned x, y;

	for (unsigned row = 0; row < gridHeight; row++) {
			for (unsigned col = 0; col < gridWidth; col++) {
				Cell* cell = (*map)(row, col);

				unsigned cellColor = Map::getCellImageColor(row, col, image, width, height, PixelsToCell);
				if (cellColor == Map::IMAGE_COLOR_OBSTACLE) {
					cell->setCost(Cell::COST_UNWALKABLE);
				} else if (cellColor == Map::IMAGE_COLOR_CLEAR) {
					cell->setCost(Cell::COST_CLEAR);
				}
			}
		}

}

