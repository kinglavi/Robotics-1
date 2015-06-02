/*
 * MovementManager.cpp
 *
 *  Created on: Jun 2, 2015
 *      Author: colman
 */

#include "MovementManager.h"

MovementManager::MovementManager() {
	pc = new PlayerClient("localhost", 6665);
	lp = new LaserProxy(&pc);
	pp = new Position2dProxy(&pc);
}

MovementManager::~MovementManager() {
	// TODO Auto-generated destructor stub
}

bool GetRelativePrespective(LaserProxy lp)
	{
		for (int i=280; i<370; i++)
		{
			if (lp[i] < 0.8)
				return true;
		}
		return false;
	}



