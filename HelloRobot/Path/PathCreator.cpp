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

#define DEBUG_LISTS 1
#define DEBUG_LIST_LENGTHS_ONLY 0

using namespace std;

namespace Path {

PathCreator::PathCreator() {
	// TODO Auto-generated constructor stub

}

PathCreator::~PathCreator() {
	// TODO Auto-generated destructor stub
}

vector<Cell*> PathCreator::CreatePath(Cell* start, Cell* dest) {
	PutWeights();
	ConfigurationManager::Instance()->GetMap()->PrintGrid(start, dest);
//	string strPath = A_Star::pathFind(start, dest); // still unchecked
	vector<Cell*> path = RunAStar(start, dest);
	ConfigurationManager::Instance()->GetMap()->PrintGrid(start, dest, path);
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

<<<<<<< HEAD
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
				((MapSearchNode *)p)->PrintNodeInfo();
				p = astarsearch.GetOpenListNext();

			}

			cout << "Open list has " << len << " nodes\n";

			len = 0;

			cout << "Closed:\n";
			p = astarsearch.GetClosedListStart();
			while( p )
			{
				len++;
				p->PrintNodeInfo();
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

vector<Coordinates> PathCreator::SmoothPath(vector<Cell*> cellsPath, Coordinates start, Coordinates end)
{
	vector<Coordinates> originPath;
	originPath.push_back(start);
//	for (int i = 0; i = cellsPath.size(); );
	return originPath;
}

bool PathCreator::IsStraitApprocah(Coordinates StartCoordinateInCM, Coordinates EndCoordinateInCM)
=======
bool PathCreator::IsStraitApprocah(Coordinates* StartCoordinateInCM, Coordinates* EndCoordinateInCM)
>>>>>>> branch 'master' of https://github.com/mkobi/Robotics.git
{
		Map* map = ConfigurationManager::Instance()->GetMap();
		vector<vector<Cell*> > grid = ConfigurationManager::Instance()->GetMap()->Grid;

		// Checks the angle of the two locations.
		bool isBluntAngle = (fabs(EndCoordinateInCM->Y - StartCoordinateInCM->Y) > fabs(EndCoordinateInCM->X - StartCoordinateInCM->X));
		if (isBluntAngle) {
			swap(StartCoordinateInCM->X, StartCoordinateInCM->Y);
			swap(EndCoordinateInCM->X, EndCoordinateInCM->Y);
		}

		// Makes the higher valued coordinate in the end location.
		if (StartCoordinateInCM->X > EndCoordinateInCM->X) {
			swap(StartCoordinateInCM->X, EndCoordinateInCM->X);
			swap(StartCoordinateInCM->Y, EndCoordinateInCM->Y);
		}

		float xDelta = EndCoordinateInCM->X - StartCoordinateInCM->X;
		float yDelta = fabs(EndCoordinateInCM->Y - StartCoordinateInCM->Y);

		float error = xDelta / 2.0f;
		int yStep = (StartCoordinateInCM->Y < EndCoordinateInCM->Y) ? 1 : -1;
		int y = (int) StartCoordinateInCM->Y;

		int maxX = (int) EndCoordinateInCM->X;

		int x;
		for (x = (int) StartCoordinateInCM->X; x < maxX; x++) {
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

vector<Coordinates*> PathCreator::GetFinalPath(Cell* start, Cell* dest) {
		vector<Cell*> InitialPath = CreatePath(start, dest);
/*		if (InitialPath.empty()) {
			cout << "There is no valid path to destination." << endl;
			return InitialPath;
		}*/

		vector<Coordinates*> waypoints;
		unsigned lastTakenWaypointIndex = 0;
		for (unsigned waypointIndex = 0; waypointIndex < InitialPath.size(); waypointIndex++) {
			Coordinates* currentWaypointWorldLocation = InitialPath[waypointIndex]->getWorldLocationCm();
			if (waypointIndex == 0 || waypointIndex == InitialPath.size() - 1 || waypointIndex - lastTakenWaypointIndex >= MAX_WAYPOINT_SPACING) {
				lastTakenWaypointIndex = waypointIndex;
				waypoints.push_back(currentWaypointWorldLocation);
			} else {
				Coordinates* lastWaypointWorldLocation = waypoints.back();
				if (!IsStraitApprocah(lastWaypointWorldLocation, currentWaypointWorldLocation)) {
					lastTakenWaypointIndex = waypointIndex - 1;
					Coordinates* lastWaypointWorldLocation = InitialPath[lastTakenWaypointIndex]->getWorldLocationCm();
					waypoints.push_back(lastWaypointWorldLocation);
				}
			}
		}

		return waypoints;
	}

} /* namespace Path */
