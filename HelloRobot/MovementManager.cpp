/*
 * MovementManager.cpp
 *
 *  Created on: Jun 2, 2015
 *      Author: colman
 */

#include "MovementManager.h"

MovementManager::MovementManager() {
	pc = new PlayerClient("localhost", 6665);
	lp = new LaserProxy(pc);
	pp = new Position2dProxy(pc);

	Position* pos = GetRobotsPosition();
	pp->SetOdometry(pos->x,pos->y,pos->yaw);

}

bool MovementManager::GetRelativePrespective() {
	for (int i=280; i<370; i++)
	{
		if ((*lp)[i] < 0.8)
			return true;
	}
	return false;
}

Position* MovementManager::GetRobotsPosition()
{
	double x = pp->GetXPos();
	double y = pp->GetYPos();
	double yaw = pp->GetYaw();

	Position* position = new Position(x,y,yaw);

	cout << "position: (" << x << "," << y << "," <<
	yaw << ")" << endl;

	return position;
}

double MovementManager::getAlpha()
{

}



