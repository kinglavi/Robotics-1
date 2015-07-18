#include <vector>
#include "../Mapping/Cell.h"
#include "../Common/ConfigurationManager.h"
#include "pngUtil.h"
#include "Map.h"
#include <float.h>

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

	for (unsigned i = 0; i < height; i++) {
		for (unsigned j = 0; j < width; j++) {
			vector<Cell*> nbrs;
			// Top
			if (i != 0) {
				if (j != 0) {
					// Top left
					nbrs.push_back(Grid[i - 1][j - 1]);
				}
				// Top middle
				nbrs.push_back(Grid[i - 1][j]);
				if (j < width - 1) {
					// Top right
					nbrs.push_back(Grid[i - 1][j + 1]);
				}
			}
			if (j < width - 1) {
				// Middle right
				nbrs.push_back(Grid[i][j + 1]);
			}
			// Bottom
			if (i < height - 1) {
				if (j < width - 1) {
					// Bottom right
					nbrs.push_back(Grid[i + 1][j + 1]);
				}
				// Bottom middle
				nbrs.push_back(Grid[i + 1][j]);
				if (j != 0) {
					// Bottom left
					nbrs.push_back(Grid[i + 1][j - 1]);
				}
			}
			if (j != 0) {
				// Middle left
				nbrs.push_back(Grid[i][j - 1]);
			}
			Grid[i][j]->setNeighbors(nbrs);
		}
	}
}

void Map::CreateGrid(unsigned paddingSize)
{
	double gridRes = ConfigurationManager::getConfig()->GetMap()->GridResolutionCM;
	double mapRes = ConfigurationManager::getConfig()->GetMap()->Cm_To_Pixel_Ratio;
	char* path = StringHelper::ConvertStringToCharArray(this->Map_Path);
	char* filename = pngUtil::PadMap(path, paddingSize);
	double PixelsToCell = gridRes/mapRes;
	unsigned width, height;

	std::vector<unsigned char> image;

	unsigned error = lodepng::decode(image, width, height, filename);

	Grid_Height= height/PixelsToCell;
	Grid_Width = width/PixelsToCell;

	Initialize(Grid_Height, Grid_Width);

	for (int row = 0; row < Grid_Height; row++)
	{
		for (int col = 0; col < Grid_Width; col++)
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

	Cell* Map::getCellFromLocation(int row, int col) const
	{
		double gridRes = ConfigurationManager::getConfig()->GetMap()->GridResolutionCM;
		double mapRes = ConfigurationManager::getConfig()->GetMap()->Cm_To_Pixel_Ratio;
		double PixelsToCell = gridRes/mapRes;
		row = row/PixelsToCell;
		col = col/PixelsToCell;
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
			for (unsigned j = 0; j < Grid_Width; j++)
					{
				double cost = (int)Grid[i][j]->getCost();
				char dis;
				if (cost < 0) {
					dis = '#';
				}
				else {
					dis = (char)((int)cost + '0');
				}
				cout << dis;
			}
		}
		cout << endl;
		cout << endl;
		cout << endl;
	}
}
