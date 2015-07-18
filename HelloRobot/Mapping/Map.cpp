/*
 * Map.cpp
 *
 *  Created on: Jun 16, 2015
 *      Author: colman
 */

#include <vector>

#include "../Mapping/Cell.h"
#include "../Common/ConfigurationManager.h"
#include "pngUtil.h"
#include "Map.h"
using namespace Common;
using namespace Mapping;

namespace Mapping{

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

Map::Map(unsigned height, unsigned width) {
	Initialize(height, width);
}

Map::Map(const Map& map) :
		Grid_Height(map.Grid_Height), Grid_Width(map.Grid_Width) {
	Initialize(map.Grid_Height, map.Grid_Width);

	for (int row = 0; row < map.Grid_Height; row++) {
		for (int col = 0; col < map.Grid_Width; col++) {
			Cell* cell = new Cell(row, col);
			Grid[row][col] = new Cell(*cell);
		}
	}
}

void Map::Initialize(unsigned height, unsigned width)
{
	Grid.resize(height);
	for (unsigned i = 0; i < height; i++) {
		Grid[i].resize(width);
		for (unsigned j = 0; j < width; j++) {
			// Initialize cells
			Grid[i][j] = new Cell(i,j);
		}
	}
}

void Map::CreateGrid(unsigned paddingSize, int MapResolutionCM, int GridResolutionCM)
{
	char* path = StringHelper::ConvertStringToCharArray(this->Map_Path);
	char* filename = pngUtil::PadMap(path, paddingSize);
	double PixelsToCell = GridResolutionCM/MapResolutionCM;
	unsigned width, height;

	std::vector<unsigned char> image;

	unsigned error = lodepng::decode(image, width, height, filename);

	int gridHeight = height/PixelsToCell;
	int gridWidth = width/PixelsToCell;

	Initialize(gridHeight, gridWidth);

	int x, y;

	for (int row = 0; row < gridHeight; row++)
	{
			for (int col = 0; col < gridWidth; col++)
			{
				Cell* cell = getCell(row, col);

				unsigned cellColor = Map::getCellImageColor(row, col, image, width, height, PixelsToCell);
				if (cellColor == Map::IMAGE_COLOR_OBSTACLE) {
					cell->setCost(Cell::COST_UNWALKABLE);
				} else if (cellColor == Map::IMAGE_COLOR_CLEAR) {
					cell->setCost(Cell::COST_CLEAR);
				}
			}
		}

	PrintGrid();
	}

	Cell* Map::getCell(int row, int col) const
	{
		if (!isInRange(row, col))
		{
			return NULL;
		}

		return Grid[row][col];
	}

	bool Map::isInRange(int row, int col) const
	{
		return row >= 0 && row < (int) Grid_Height && col >= 0 && col < (int) Grid_Width;
	}

	void Map::PrintGrid()
	{
		for (unsigned i = 0; i < Grid_Height; i++)
		{
			cout << endl;
			for (unsigned j = 0; j < Grid_Height; j++)
			{
				cout << (int)Grid[i][j]->getCost();
			}
		}
	}
}
