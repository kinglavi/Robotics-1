/*
 * PathCreator.cpp
 *
 *  Created on: Jul 18, 2015
 *      Author: colman
 */

#include "PathCreator.h"
#include "../Common/ConfigurationManager.h"

#include "AStarSearch.h"
#include "MapSearchNode.h"

#include <iostream>
#include <stdio.h>
#include <math.h>
using namespace Common;

#define DEBUG_LISTS 0
#define DEBUG_LIST_LENGTHS_ONLY 0

using namespace std;

namespace Path {

PathCreator::PathCreator() {
	// TODO Auto-generated constructor stub

}

PathCreator::~PathCreator() {
	// TODO Auto-generated destructor stub
}

vector<Coordinates*> PathCreator::CreatePath(Coordinates* start, Coordinates* end) {
	Cell* startCell = ConfigurationManager::Instance()->GetMap()->getCellFromLocation(start->X, start->Y);
	Cell* endCell = ConfigurationManager::Instance()->GetMap()->getCellFromLocation(end->X, end->Y);
	PutWeights();
	ConfigurationManager::Instance()->GetMap()->PrintGrid(startCell, endCell);
	vector<Cell*> path = RunAStar(startCell, endCell);
	ConfigurationManager::Instance()->GetMap()->PrintGrid(startCell, endCell, path);
	vector<Coordinates*> smoothPath = SmoothPath(path, start, end);
	ConfigurationManager::Instance()->GetMap()->PrintGrid(startCell, endCell, smoothPath);
	return smoothPath;
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
				vector<Cell*>* ns = current->getNeighbors();
				for (int n = 0; n < ns->size(); n++)
				{
					Cell* current = ns->at(n);
					if (current->getCost() == Cell::COST_CLEAR && (std::find(cellsToColorThisTime.begin(), cellsToColorThisTime.end(),current) == cellsToColorThisTime.end()))
					{
						cellsToColorThisTime.push_back(current);
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
			current->setCost(layer + 2);
			vector<Cell*>* ns = current->getNeighbors();
			for (int n = 0; n < ns->size(); n++)
			{
				Cell* nextToMe = (*ns)[n];
				if (nextToMe->getCost() == Cell::COST_CLEAR && (std::find(cellsToColorNextTime.begin(), cellsToColorNextTime.end(), (*ns)[n]) == cellsToColorNextTime.end()))
				{
					cellsToColorNextTime.push_back(nextToMe);
				}
			}
		}

		cellsToColorThisTime = cellsToColorNextTime;
		cellsToColorNextTime.clear();
	}
}

vector<Cell*> PathCreator::RunAStar(Cell* start, Cell* end)
{

	AStarSearch astarsearch;

	unsigned int SearchCount = 0;

	const unsigned int NumSearches = 1;

	while(SearchCount < NumSearches)
	{

//		// Create a start state
		MapSearchNode nodeStart;
		nodeStart.row = start->getRow();
		nodeStart.col = start->getCol();

		// Define the goal state
		MapSearchNode nodeEnd;
		nodeEnd.row = end->getRow();
		nodeEnd.col = end->getCol();

		// Set Start and goal states

		astarsearch.SetStartAndGoalStates( nodeStart, nodeEnd );

		unsigned int SearchState;
		unsigned int SearchSteps = 0;

		vector<Cell*> path;

		do
		{
			SearchState = astarsearch.SearchStep();

			SearchSteps++;

	#if DEBUG_LISTS

			cout << "Steps:" << SearchSteps << "\n";

			int len = 0;

			cout << "Open:\n";
			MapSearchNode *p = astarsearch.GetOpenListStart();
			while( p )
			{
				len++;
	#if !DEBUG_LIST_LENGTHS_ONLY
				((MapSearchNode *)p)->PrintNodeInfo();
	#endif
				p = astarsearch.GetOpenListNext();

			}

			cout << "Open list has " << len << " nodes\n";

			len = 0;

			cout << "Closed:\n";
			p = astarsearch.GetClosedListStart();
			while( p )
			{
				len++;
	#if !DEBUG_LIST_LENGTHS_ONLY
				p->PrintNodeInfo();
	#endif
				p = astarsearch.GetClosedListNext();
			}

			cout << "Closed list has " << len << " nodes\n";
	#endif

		}
		while( SearchState == AStarSearch::SEARCH_STATE_SEARCHING );

		if( SearchState == AStarSearch::SEARCH_STATE_SUCCEEDED )
		{
			cout << "Search found goal state\n";

				MapSearchNode *node = astarsearch.GetSolutionStart();

	#if DISPLAY_SOLUTION
				cout << "Displaying solution\n";
	#endif
				int steps = 0;

				Cell* cell = ConfigurationManager::Instance()->GetMap()->getCell(node->row, node->col);
				path.push_back(cell);
				for( ;; )
				{
					node = astarsearch.GetSolutionNext();

					if( !node )
					{
						break;
					}

					cell = ConfigurationManager::Instance()->GetMap()->getCell(node->row, node->col);
					path.push_back(cell);
					steps ++;

				};

				cout << "Solution steps " << steps << endl;

				// Once you're done with the solution you can free the nodes up
				astarsearch.FreeSolutionNodes();
		}
		else if( SearchState == AStarSearch::SEARCH_STATE_FAILED )
		{
			cout << "Search terminated. Did not find goal state\n";

		}

		// Display the number of loops the search went through
		cout << "SearchSteps : " << SearchSteps << "\n";

		SearchCount ++;

		astarsearch.EnsureMemoryFreed();

		return path;
	}
}


vector<Coordinates*> PathCreator::SmoothPath(vector<Cell*> cellsPath, Coordinates* start, Coordinates* end)
{
	vector<Coordinates*> originPath;

	originPath.push_back(start);
	for (int i = 0; i < cellsPath.size(); i++)
	{
		originPath.push_back(ConfigurationManager::Instance()->GetMap()->CellToCoordinateOfCenterCell(cellsPath[i]));
	}
	originPath.push_back(end);

	vector<Coordinates*> coolPath;
	unsigned lastCoordinate = 0;
	for (unsigned i = 0; i < originPath.size(); i++) {
		Coordinates* currentCoordinate = originPath[i];
		if (i == 0 || i == originPath.size() - 1 || i - lastCoordinate >= MAX_WAYPOINT_SPACING) {
			lastCoordinate = i;
			coolPath.push_back(currentCoordinate);
		} else {
			Coordinates* lastWaypointWorldLocation = coolPath.back();
			if (!IsStraightApproche(lastWaypointWorldLocation, currentCoordinate)) {
				lastCoordinate = i - 1;
				Coordinates* lastWaypointWorldLocation = originPath[lastCoordinate];
				coolPath.push_back(lastWaypointWorldLocation);
			}
		}
	}

	return coolPath;
}

bool PathCreator::IsStraightApproche(Coordinates* startCoordinate, Coordinates* endCoordinate)
{
		Map* map = ConfigurationManager::Instance()->GetMap();
		vector<vector<Cell*> > grid = ConfigurationManager::Instance()->GetMap()->Grid;
		double gridRes = ConfigurationManager::Instance()->GetMap()->GridResolutionCM;
		double mapRes = ConfigurationManager::Instance()->GetMap()->Cm_To_Pixel_Ratio;
		double PixelsToCell = gridRes/mapRes;

		float sizeOfMovement = PixelsToCell/2;
		float diffX = fabs(endCoordinate->X - startCoordinate->X);
		float diffY = fabs(endCoordinate->Y - startCoordinate->Y);
		float angle = atan(diffY/diffX);
		float dx = cos(angle) * sizeOfMovement;
		float dy = sin(angle) * sizeOfMovement;

		if (startCoordinate->X > endCoordinate->X)
		{
			dx = -dx;
		}

		if (startCoordinate->Y > endCoordinate->Y)
		{
			dy = -dy;
		}

		float currentX = startCoordinate->X;
		float currentY = startCoordinate->Y;
		double distanceX = fabs(currentX - endCoordinate->X);
		double distanceY = fabs(currentY - endCoordinate->Y);
		float absdx = fabs(dx);
		float absdy = fabs(dy);
		while ((currentX != endCoordinate->X && distanceX > absdx) &&
				(currentY != endCoordinate->Y && distanceY > absdy))
		{
			currentX += dx;
			currentY += dy;
			if (!map->CmCoordinateToCell(currentX, currentY)->isWalkable()) {
				return false;
			}

			distanceY = fabs(currentY - endCoordinate->Y);
			distanceX = fabs(currentX - endCoordinate->X);
		}

		return true;
	}
} /* namespace Path */

