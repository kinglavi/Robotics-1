/*
 * MovementManager.cpp
 *
 *  Created on: Jun 2, 2015
 *      Author: colman
 */

#include "MovementManager.h"
#include "ConfigurationManager.h"

using namespace Common;

MovementManager::MovementManager() {}

void MovementManager::GetObastaclePosition()
{

}

double MovementManager::GetLazerAngle(int lazerReadingIndex)
{
	return ((lazerReadingIndex - 333)*0.36);
}

vector<Obstacle*> MovementManager::GetRelativePrespective()
{
	vector<Obstacle*> obstacles;
	LaserProxy* lp = ConfigurationManager::Instance()->GetRobot()->laserProxy;

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

double MovementManager::getAlpha()
{

}



