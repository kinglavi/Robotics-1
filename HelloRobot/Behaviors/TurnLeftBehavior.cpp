/*
 * TurnLeftBehavior.cpp
 *
 *  Created on: Jul 19, 2015
 *      Author: colman
 */

#include "TurnLeftBehavior.h"
#include "../Common/ConfigurationManager.h"
#include "../Common/ConvertionHandler.h"
using namespace Common;

namespace Behaviors {


TurnLeftBehavior::TurnLeftBehavior(PathManager* pathManager) : Behavior(pathManager) {
	_robot = ConfigurationManager::Instance()->GetRobot();
}

TurnLeftBehavior::~TurnLeftBehavior() {
	// TODO Auto-generated destructor stub
}

bool TurnLeftBehavior::ShouldTurnLeft()
{
	Coordinates* robotPosition = _robot->GetRobotsPosition();
	Coordinates* nextInLine = _pathManager->GetNextCoordinateInPath();
	double angle = CalcAngle(robotPosition, nextInLine);
	cout << "Robot's angle=" << robotPosition->Yaw << " Desired angle=" << angle << endl;
	return fabs(angle - robotPosition->Yaw) < 2;
}

double TurnLeftBehavior::CalcAngle(Coordinates* first, Coordinates* second)
{
	double deltaX = first->X - second->X;
	double deltaY = first->Y - second->Y;

	double angleToDest = atan2(deltaY, deltaX);

	if (deltaY < 0)
	{
		angleToDest += M_PI;
	}

	angleToDest = ConvertionHandler::makeAngleNormal(angleToDest);

	return radiansToDegrees(angleToDest);
}


bool TurnLeftBehavior::startCond()
{
	return !ShouldTurnLeft();
}

bool TurnLeftBehavior::stopCond()
{
	bool stop = ShouldTurnLeft();
	if (stop)
	{
		_robot->setSpeed(0, 0);
	}

	return stop;
}

void TurnLeftBehavior::action()
{
	double newYawSpeed = MaxYawChangeSpeed -20;
	_robot->setSpeed(0, degreesToRadians(newYawSpeed));
}

} /* namespace Path */
