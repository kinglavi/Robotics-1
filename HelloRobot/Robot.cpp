/*
 * Robot.cpp
 *
 *  Created on: Jun 16, 2015
 *      Author: colman
 */

#include "Robot.h"

Robot::Robot()
{
	playerClient = new PlayerClient("localhost", 6665);
	laserProxy = new LaserProxy(playerClient);
	position2dProxy = new Position2dProxy(playerClient);

	Position* pos = GetRobotsPosition();
	position2dProxy->SetOdometry(pos->x,pos->y,pos->yaw);
}

Position* Robot::GetRobotsPosition()
{
	double x = position2dProxy->GetXPos();
	double y = position2dProxy->GetYPos();
	double yaw = position2dProxy->GetYaw();

	Position* position = new Position(x,y,yaw);

	return position;
}
