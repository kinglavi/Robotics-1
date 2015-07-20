/*
 * main.cpp
 *
 *  Created on: Jan 10, 2015
 *      Author: colman
 */

#include <libplayerc++/playerc++.h>

#include "Mapping/pngUtil.h"

#include "Common/StringHelper.h"
#include "Common/ConfigurationManager.h"
#include "Common/PathManager.h"
#include "Common/Manager.h"
using namespace Common;

#include "Behaviors/TurnLeftBehavior.h"
#include "Behaviors/MoveForward.h"
using namespace Behaviors;

#include "Path/PathCreator.h"
using namespace Path;

int main() {
	double mapRes = ConfigurationManager::Instance()->GetMap()->Cm_To_Pixel_Ratio;
	double robotSize = ConfigurationManager::Instance()->GetRobot()->Width;
	string path = ConfigurationManager::Instance()->GetMap()->Map_Path;

	ConfigurationManager::Instance()->GetMap()->CreateGrid(((robotSize/2)/mapRes));

	Coordinates* start = ConfigurationManager::Instance()->GetRobot()->GetStartLocation();

	int finishX = ConfigurationManager::Instance()->GetGoalX();
	int finishY = ConfigurationManager::Instance()->GetGoalY();

	Coordinates* goal = new Coordinates(finishX, finishY, 0);

	PathCreator* creator = new PathCreator();
	vector<Coordinates*> robotPath = creator->CreatePath(start, goal);

	PathManager* pathManager = new PathManager(robotPath);

	Manager* movementManager = new Manager(pathManager);

	movementManager->run();



	return 0;
}

