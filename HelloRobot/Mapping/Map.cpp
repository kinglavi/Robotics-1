#include <vector>
#include "../Mapping/Cell.h"
#include "../Common/ConfigurationManager.h"
#include "pngUtil.h"
#include "Map.h"
#include <float.h>
#include <algorithm>

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
			Cell* cell = new Cell(col, row);
			Grid[row][col] = new Cell(*cell);
		}
	}
}

void Map::Initialize(unsigned height, unsigned width)
{
	Grid.resize(height);
	for (unsigned row = 0; row < height; row++) {
		Grid[row].resize(width);
		for (unsigned col = 0; col < width; col++) {
			// Initialize cells
			Grid[row][col] = new Cell(row, col);
		}
	}

	for (unsigned row = 0; row < height; row++) {
		for (unsigned col = 0; col < width; col++) {
			vector<Cell*>* nbrs = new vector<Cell*>();
			// Top
			if (row != 0) {
				if (col != 0) {
					// Top left
					nbrs->push_back(Grid[row - 1][col - 1]);
				}
				// Top middle
				nbrs->push_back(Grid[row - 1][col]);
				if (col < width - 1) {
					// Top right
					nbrs->push_back(Grid[row - 1][col + 1]);
				}
			}
			if (col < width - 1) {
				// Middle right
				nbrs->push_back(Grid[row][col + 1]);
			}
			// Bottom
			if (row < height - 1) {
				if (col < width - 1) {
					// Bottom right
					nbrs->push_back(Grid[row + 1][col + 1]);
				}
				// Bottom middle
				nbrs->push_back(Grid[row + 1][col]);
				if (col != 0) {
					// Bottom left
					nbrs->push_back(Grid[row + 1][col - 1]);
				}
			}
			if (col != 0) {
				// Middle left
				nbrs->push_back(Grid[row][col - 1]);
			}
			Grid[row][col]->setNeighbors(nbrs);
		}
	}
}

void Map::CreateGrid(unsigned paddingSize)
{
	double gridRes = ConfigurationManager::Instance()->GetMap()->GridResolutionCM;
	double mapRes = ConfigurationManager::Instance()->GetMap()->Cm_To_Pixel_Ratio;
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

	Cell* Map::getCellFromLocation(int x, int y) const
	{
		double gridRes = ConfigurationManager::Instance()->GetMap()->GridResolutionCM;
		double mapRes = ConfigurationManager::Instance()->GetMap()->Cm_To_Pixel_Ratio;
		double PixelsToCell = gridRes/mapRes;
		int row = y/PixelsToCell;
		int col = x/PixelsToCell;
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
		for (unsigned row = 0; row < Grid_Height; row++)
		{
			cout << endl;
			for (unsigned col = 0; col < Grid_Width; col++)
					{
				double cost = (int)Grid[row][col]->getCost();
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

	void Map::PrintGrid(Cell* start, Cell* end)
	{
		vector<Cell*> emptyPath;
		PrintGrid(start, end, emptyPath);
	}

	void Map::PrintGrid(Cell* start, Cell* end, vector<Coordinates*> path)
	{
		vector<Cell*> cells;
		for (int i = 0; i < path.size(); i++)
		{
			cells.push_back(getCellFromLocation(path[i]->X, path[i]->Y));
		}
		PrintGrid(start, end, cells);
	}

	void Map::PrintGrid(Cell* start, Cell* end, vector<Cell*> path)
	{


		for (unsigned row = 0; row < Grid_Height; row++)
		{
			cout << endl;
			for (unsigned col = 0; col < Grid_Width; col++)
			{
				Cell* currentCell = Grid[row][col];

				double cost = (int)currentCell->getCost();
				char dis;
				if (cost < 0) {
					dis = '#';
				}
				else {
					dis = (char)((int)cost + '0');
				}

				if(dis != '#' && std::find(path.begin(), path.end(), currentCell) != path.end())
				{
					dis = 'X';
				}

				if (start->getRow() == row && start->getCol() == col)
				{
					dis = 'S';
				}

				if (end->getRow() == row && end->getCol() == col)
				{
					dis = 'E';
				}

				cout << dis;
			}
		}
		cout << endl;
		cout << endl;
		cout << endl;
	}

	Cell* Map::CmCoordinateToCell(double x, double y) const {
		double gridRes = ConfigurationManager::Instance()->GetMap()->GridResolutionCM;
		double mapRes = ConfigurationManager::Instance()->GetMap()->Cm_To_Pixel_Ratio;
		double PixelsToCell = gridRes/mapRes;
		unsigned row = y / PixelsToCell;
		unsigned col = x / PixelsToCell;

		return getCell(row, col);
	}

	Coordinates* Map::CellToCoordinateOfCenterCell(Cell* cell) const {
		double gridRes = ConfigurationManager::Instance()->GetMap()->GridResolutionCM;
		double mapRes = ConfigurationManager::Instance()->GetMap()->Cm_To_Pixel_Ratio;
		double PixelsToCell = gridRes/mapRes;

		unsigned y = (cell->getRow() * PixelsToCell) + PixelsToCell/2;// place it in the center of the cell
		unsigned x = (cell->getCol() * PixelsToCell) + PixelsToCell/2; // place it in the center of the cell

		return new Coordinates(x, y, 0);
	}

}
