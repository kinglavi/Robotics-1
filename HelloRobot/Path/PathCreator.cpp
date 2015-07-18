/*
 * PathCreator.cpp
 *
 *  Created on: Jul 18, 2015
 *      Author: colman
 */

#include "PathCreator.h"

namespace Path {

PathCreator::PathCreator() {
	// TODO Auto-generated constructor stub

}

PathCreator::~PathCreator() {
	// TODO Auto-generated destructor stub
}

vector<Cell*> PathCreator::CreatePath(Grid* grid, Cell* start, Cell* dest) {
	PutWeights(grid);
	vector<Cell*> path; //the raw pixels
	return path;
}

void PathCreator::PutWeights(Grid* grid) {
	unsigned cols = grid->ColumnsCount;
	unsigned rows = grid->RowsCount;
	vector<Cell*> cellsToColorNextTime;
	vector<Cell*> cellsToColorThisTime;
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			Cell* current = grid->Cells[i][j];
			if (current->getCost() == Cell::COST_UNWALKABLE)
			{
				vector<Cell*> ns = current->getNeighbors();
				for (int n = 0; n < ns.size(); n++)
				{
					cellsToColorThisTime.push_back(ns[n]);
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
				if (nextToMe->getCost() == Cell::COST_CLEAR)
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