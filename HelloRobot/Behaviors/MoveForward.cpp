/*
 * MoveForward.cpp
 *
 *  Created on: May 26, 2015
 *      Author: colman
 */

#include "MoveForward.h"
#include "../Common/ConfigurationManager.h"
using namespace Common;

#define MIN_ANGLE -30
#define MAX_ANGLE 30
#define MAX_DIST_TO_OBSTACLE 0.5
#define FORWARD_SPEED 15

namespace Behaviors {
	MoveForward::MoveForward(PathManager* pathManager) : Behavior(pathManager) {
		_robot = ConfigurationManager::Instance()->GetRobot();
	}

	MoveForward::~MoveForward() {
		// TODO Auto-generated destructor stub
	}

	bool MoveForward::checkObstacleInFront()
	{
		bool isObstacleInFront = false;
		int minIndex = Robot::deg_to_index(MIN_ANGLE);
		int maxIndex = Robot::deg_to_index(MAX_ANGLE);

		vector<float> scan = _robot->getLaserScan();

		for (int i = minIndex; i <= maxIndex; i += 10)
		{
			if (scan[i] < MAX_DIST_TO_OBSTACLE)
			{
				isObstacleInFront = true;
				break;
			}
		}

		return isObstacleInFront;
	}

	bool MoveForward::checkIfReachedTarget()
	{
		Coordinates* next = _pathManager->GetNextCoordinateInPath();
		Coordinates* current = _robot->GetRobotsPosition();
		cout << "Robot X=" << current->X << " Y=" << current->Y << " Target X=" << next->X << " Y=" << next->Y << endl;
		if (ConvertionHandler::aboutEquals(next->X, current->X, 4) && ConvertionHandler::aboutEquals(next->Y, current->Y, 4))
		{
			_pathManager->MoveToNextCoordinate();
			return true;
		}
		return false;
	}


	bool MoveForward::startCond()
	{
		return !checkIfReachedTarget();
	}

	bool MoveForward::stopCond()
	{
		bool stop = checkIfReachedTarget();
		if (stop)
		{
			_robot->setSpeed(0, 0);
		}

		return stop;
	}

	void MoveForward::action()
	{
		_robot->setSpeed(FORWARD_SPEED, 0);
	}
}
