#pragma once

#include <vector>
using namespace std;

class MapSearchNode
{
public:
	int row;	 // the (x,y) positions of the node
	int col;

	MapSearchNode() { row = col = 0; }
	MapSearchNode( int prevRow, int prevCol ) { row=prevRow; col=prevCol; }

	float GoalDistanceEstimate( MapSearchNode &nodeGoal );
	bool IsGoal( MapSearchNode &nodeGoal );
	vector<MapSearchNode*> GetSuccessors( MapSearchNode *parent_node );
	float GetCost( MapSearchNode &successor );
	bool IsSameState( MapSearchNode &rhs );

	void PrintNodeInfo();


};



