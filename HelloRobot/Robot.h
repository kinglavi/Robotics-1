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
#include <stdexcept>
#include "ConvertionHandler.h"

using namespace PlayerCc;
using namespace std;

class Robot {
public:
	Robot();
	void Read();
	void setSpeed(double forward_CmPerSec, double angular_RadiansPerSec);
	float* getLaserScan();
	static double index_to_deg(int index);
	static unsigned deg_to_index(double degree);
	int Width;
	int Height;

	PlayerClient* playerClient;
	LaserProxy* laserProxy;
	Position2dProxy* position2dProxy;

	Position* GetRobotsPosition();
};

#endif /* ROBOT_H_ */
