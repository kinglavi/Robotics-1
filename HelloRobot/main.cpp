/*
 * main.cpp
 *
 *  Created on: Jan 10, 2015
 *      Author: colman
 */

#include <libplayerc++/playerc++.h>

#include "Mapping/pngUtil.h"

#include "Common/MovementManager.h"
#include "Common/StringHelper.h"
#include "Common/ConfigurationManager.h"
using namespace Common;

#include "Path/PathCreator.h"
using namespace Path;

int main() {
	double mapRes = ConfigurationManager::Instance()->GetMap()->Cm_To_Pixel_Ratio;
	double robotSize = ConfigurationManager::Instance()->GetRobot()->Width;
	string path = ConfigurationManager::Instance()->GetMap()->Map_Path;

	ConfigurationManager::Instance()->GetMap()->CreateGrid(((robotSize/2)/mapRes));

	int startX = ConfigurationManager::Instance()->GetStartX();
	int startY = ConfigurationManager::Instance()->GetStartY();
	Cell* startCell = ConfigurationManager::Instance()->GetMap()->getCellFromLocation(startY, startX);
	int finishX = ConfigurationManager::Instance()->GetGoalX();
	int finishY = ConfigurationManager::Instance()->GetGoalY();
	Cell* goalCell = ConfigurationManager::Instance()->GetMap()->getCellFromLocation(finishY, finishX);

	PathCreator* creator = new PathCreator();
	vector<Cell*> robotPath = creator->CreatePath(startCell, goalCell);

	MovementManager* manager = new MovementManager();
	Robot* robot = ConfigurationManager::Instance()->GetRobot();
	vector<Obstacle*> obs = manager->GetRelativePrespective();
	vector<Obstacle*>::iterator i;

	for(i=obs.begin(); i!=obs.end(); i++)
	{
		cout << "Angle: " << (*i)->Angle << ", Distance: " << (*i)->Distance << endl;
	}

	while (true) {
		//robot->playerClient->Read();


/*		if(manager->GetRelativePrespective())
			manager->pp->SetSpeed(0.0,0.3);
		else
			manager->pp->SetSpeed(0.8,0.0);*/

		//robot->GetRobotsPosition();
	}

	return 0;
}

