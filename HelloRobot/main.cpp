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
	double mapRes = ConfigurationManager::getConfig()->GetMap()->Cm_To_Pixel_Ratio;
	double robotSize = ConfigurationManager::getConfig()->GetRobot()->Width;
	string path = ConfigurationManager::getConfig()->GetMap()->Map_Path;

	ConfigurationManager::getConfig()->GetMap()->CreateGrid(((robotSize/2)/mapRes));

	int startX = ConfigurationManager::getConfig()->GetStartX();
	int startY = ConfigurationManager::getConfig()->GetStartY();
	Cell* startCell = ConfigurationManager::getConfig()->GetMap()->getCellFromLocation(startX, startY);
	int finishX = ConfigurationManager::getConfig()->GetGoalX();
	int finishY = ConfigurationManager::getConfig()->GetGoalY();
	Cell* goalCell = ConfigurationManager::getConfig()->GetMap()->getCellFromLocation(finishX, finishY);

	PathCreator* creator = new PathCreator();
	vector<Cell*> robotPath = creator->CreatePath(startCell, goalCell);

	MovementManager* manager = new MovementManager();
	Robot* robot = ConfigurationManager::getConfig()->GetRobot();
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

