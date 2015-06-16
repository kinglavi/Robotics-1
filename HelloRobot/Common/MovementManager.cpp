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

void MovementManager::GetObastaclePosition()
{
	Position* pos = GetRobotsPosition();
}

double MovementManager::GetLazerAngle(int lazerReadingIndex)
{
	return ((lazerReadingIndex - 333)*0.36);
}

vector<Obstacle*> MovementManager::GetRelativePrespective()
{
	vector<Obstacle*> obstacles;

	// Getting only the relevant readings in front of the robot.
	for (int i=0; i<666; i++)
	{
		if ((*lp)[i] < 0.8)
		{
			Obstacle* obs = new Obstacle(GetLazerAngle(i), (*lp)[i]);
			obstacles.push_back(obs);
		}
	}

	return obstacles;
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



