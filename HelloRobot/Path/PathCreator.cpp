/*
 * PathCreator.cpp
 *
 *  Created on: Jul 18, 2015
 *      Author: colman
 */

#include "PathCreator.h"
#include "../Common/ConfigurationManager.h"
#include "AStar.h"
#include <algorithm>
using namespace Common;

namespace Path {

PathCreator::PathCreator() {
	// TODO Auto-generated constructor stub

}

PathCreator::~PathCreator() {
	// TODO Auto-generated destructor stub
}

vector<Cell*> PathCreator::CreatePath(Cell* start, Cell* dest) {
	PutWeights();
	ConfigurationManager::Instance()->GetMap()->PrintGrid();
	string strPath = A_Star::pathFind(start, dest); // still unchecked
	vector<Cell*> path; //the raw pixels
	return path;
}

void PathCreator::PutWeights() {
	vector<vector<Cell*> > grid = ConfigurationManager::Instance()->GetMap()->Grid;
	unsigned cols = ConfigurationManager::Instance()->GetMap()->Grid_Width;
	unsigned rows = ConfigurationManager::Instance()->GetMap()->Grid_Height;
	vector<Cell*> cellsToColorNextTime;
	vector<Cell*> cellsToColorThisTime;
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			Cell* current = grid[i][j];
			if (current->getCost() == Cell::COST_UNWALKABLE)
			{
				vector<Cell*> ns = current->getNeighbors();
				for (int n = 0; n < ns.size(); n++)
				{
					if (ns[n]->getCost() == Cell::COST_CLEAR && (std::find(cellsToColorThisTime.begin(), cellsToColorThisTime.end(), ns[n]) == cellsToColorThisTime.end()))
					{
						cellsToColorThisTime.push_back(ns[n]);
					}
				}
			}
		}
	}
	for (int layer = Cell::NUM_OF_LAYERS; layer > 0; layer--)
	{
		for (int i = 0; i < cellsToColorThisTime.size(); i++)
		{
			Cell* current = cellsToColorThisTime[i];
			current->setCost(layer);
			vector<Cell*> ns = current->getNeighbors();
			for (int n = 0; n < ns.size(); n++)
			{
				Cell* nextToMe = ns[n];
				if (nextToMe->getCost() == Cell::COST_CLEAR && (std::find(cellsToColorNextTime.begin(), cellsToColorNextTime.end(), ns[n]) == cellsToColorNextTime.end()))
				{
					cellsToColorNextTime.push_back(nextToMe);
				}
			}
		}

		cellsToColorThisTime = cellsToColorNextTime;
		cellsToColorNextTime.clear();
	}
}

bool PathCreator::IsStraitApprocah(Coordinates StartCoordinateInCM, Coordinates EndCoordinateInCM)
{
		Map* map = ConfigurationManager::Instance()->GetMap();
		vector<vector<Cell*> > grid = ConfigurationManager::Instance()->GetMap()->Grid;

		// Checks the angle of the two locations.
		bool isBluntAngle = (fabs(EndCoordinateInCM.Y - StartCoordinateInCM.Y) > fabs(EndCoordinateInCM.X - StartCoordinateInCM.X));
		if (isBluntAngle) {
			swap(StartCoordinateInCM.X, StartCoordinateInCM.Y);
			swap(EndCoordinateInCM.X, EndCoordinateInCM.Y);
		}

		// Makes the higher valued coordinate in the end location.
		if (StartCoordinateInCM.X > EndCoordinateInCM.X) {
			swap(StartCoordinateInCM.X, EndCoordinateInCM.X);
			swap(StartCoordinateInCM.Y, EndCoordinateInCM.Y);
		}

		float xDelta = EndCoordinateInCM.X - StartCoordinateInCM.X;
		float yDelta = fabs(EndCoordinateInCM.Y - StartCoordinateInCM.Y);

		float error = xDelta / 2.0f;
		int yStep = (StartCoordinateInCM.Y < EndCoordinateInCM.Y) ? 1 : -1;
		int y = (int) StartCoordinateInCM.Y;

		int maxX = (int) EndCoordinateInCM.X;

		int x;
		for (x = (int) StartCoordinateInCM.X; x < maxX; x++) {
			if (isBluntAngle) {
				if (!map->CmCoordinateToCell(y, x)->isWalkable()) {
					return false;
				}
			} else {
				if (!map->CmCoordinateToCell(x, y)->isWalkable()) {
					return false;
				}
			}

			error -= yDelta;
			if (error < 0) {
				y += yStep;
				error += xDelta;
			}
		}

		return true;
	}

} /* namespace Path */
