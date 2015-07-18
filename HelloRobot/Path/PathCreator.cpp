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
	ConfigurationManager::getConfig()->GetMap()->PrintGrid();
	string strPath = A_Star::pathFind(start, dest); // still unchecked
	vector<Cell*> path; //the raw pixels
	return path;
}

void PathCreator::PutWeights() {
	vector<vector<Cell*> > grid = ConfigurationManager::getConfig()->GetMap()->Grid;
	unsigned cols = ConfigurationManager::getConfig()->GetMap()->Grid_Width;
	unsigned rows = ConfigurationManager::getConfig()->GetMap()->Grid_Height;
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

} /* namespace Path */
