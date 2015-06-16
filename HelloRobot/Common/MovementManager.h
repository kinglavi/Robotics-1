/*
 * MovementManager.h
 *
 *  Created on: Jun 2, 2015
 *      Author: colman
 */

#ifndef MOVEMENTMANAGER_H_
#define MOVEMENTMANAGER_H_

#include <libplayerc++/playerc++.h>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <vector>
#include "../Position.h"
#include "../Obstacle.h"

using namespace PlayerCc;
using namespace std;

class MovementManager {
public:
	MovementManager();
	vector<Obstacle*> GetRelativePrespective();
	Position* GetRobotsPosition();
	void GetObastaclePosition();
	double GetLazerAngle(int lazerReadingIndex);
	double getAlpha();
	double getBeta();

	PlayerClient* pc;
	LaserProxy* lp;
	Position2dProxy* pp;
};


#endif /* MOVEMENTMANAGER_H_ */
