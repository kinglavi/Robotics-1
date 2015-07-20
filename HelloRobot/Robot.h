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
#include "Mapping/Coordinates.h"
#include <stdexcept>
#include "Common/ConvertionHandler.h"

using namespace PlayerCc;
using namespace std;
using namespace Mapping;

class Robot {
public:
	Robot();
	void Read();
	void setSpeed(double forward_CmPerSec, double angular_RadiansPerSec);
	vector<float> getLaserScan();
	static double index_to_deg(int index);
	static unsigned deg_to_index(double degree);
	inline Coordinates* GetStartLocation() { return _startLocation; }
	void SetStartLocation(Coordinates* location);
	int Width;
	int Height;

	PlayerClient* playerClient;
	LaserProxy* laserProxy;
	Position2dProxy* position2dProxy;

	Coordinates* GetRobotsPosition();
private:
	Coordinates* _startLocation;
};

#endif /* ROBOT_H_ */
