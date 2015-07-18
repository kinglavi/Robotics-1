/*
 * Robot.h
 *
 *  Created on: Jun 16, 2015
 *      Author: colman
 */

#ifndef ROBOT_H_
#define ROBOT_H_
#include <libplayerc++/playerc++.h>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <vector>
#include "Position.h"

using namespace PlayerCc;

class Robot {
public:
	Robot();
	int Width;
	int Height;

	PlayerClient* playerClient;
	LaserProxy* laserProxy;
	Position2dProxy* position2dProxy;

	Position* GetRobotsPosition();
};

#endif /* ROBOT_H_ */
