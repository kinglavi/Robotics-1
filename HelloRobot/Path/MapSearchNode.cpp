#include "MapSearchNode.h"

#include "../Common/ConfigurationManager.h"
using namespace Common;

bool MapSearchNode::IsSameState( MapSearchNode &rhs )
{

	// same state in a maze search is simply when (col,row) are the same
	if( (col == rhs.col) &&
		(row == rhs.row) )
	{
		return true;
	}
	else
	{
		return false;
	}

}

void MapSearchNode::PrintNodeInfo()
{
	char str[100];
	sprintf( str, "Node position : (%d,%d)\n", row, col );

	cout << str;
}

// Here's the heuristic function that estimates the distance from a Node
// to the Goal.

float MapSearchNode::GoalDistanceEstimate( MapSearchNode &nodeGoal )
{
	double diffX = col - nodeGoal.col;
	double diffY = row - nodeGoal.row;
	return sqrt(diffX*diffX + diffY*diffY);
}

bool MapSearchNode::IsGoal( MapSearchNode &nodeGoal )
{

	if( (col == nodeGoal.col) &&
		(row == nodeGoal.row) )
	{
		return true;
	}

	return false;
}

// This generates the successors to the given Node. It uses a helper function called
// AddSuccessor to give the successors to the AStar class. The A* specific initialisation
// is done for each node internally, so here you just set the state information that
// is specific to the application
vector<MapSearchNode*> MapSearchNode::GetSuccessors( MapSearchNode *parent_node )
{

	int parent_x = -1;
	int parent_y = -1;

	if( parent_node )
	{
		parent_x = parent_node->col;
		parent_y = parent_node->row;
	}
	vector<MapSearchNode*> nodes;
	MapSearchNode NewNode;

	Cell* thisCell = ConfigurationManager::Instance()->GetMap()->getCell(row,col);
	vector<Cell*>* nextDoor = thisCell->getNeighbors();
	for	(int i = 0; i < nextDoor->size(); i++)
	{
		Cell* nextCell = (*nextDoor)[i];
		if( (nextCell->getCost() != Cell::COST_UNWALKABLE)
			&& !((parent_y == nextCell->getRow()) && (parent_x == nextCell->getCol()))
		  )
		{
			MapSearchNode* NewNode = new MapSearchNode( nextCell->getRow(), nextCell->getCol() );
			nodes.push_back(NewNode);
		}
	}

	return nodes;
}

// given this node, what does it cost to move to successor. In the case
// of our map the answer is the map terrain value at this node since that is
// conceptually where we're moving

float MapSearchNode::GetCost( MapSearchNode &successor )
{
	return ConfigurationManager::Instance()->GetMap()->getCell(row,col)->getCost();
}
