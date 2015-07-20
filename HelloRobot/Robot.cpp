/*
 * Robot.cpp
 *
 *  Created on: Jun 16, 2015
 *      Author: colman
 */

#include "Robot.h"
#include "Common/ConfigurationManager.h"
#include <vector>
#include <libplayerc/playerc.h>

using namespace Common;

	const unsigned LASER_SAMPLES = 666;
	const double LASER_FOV_DEGREE = 240.0;

Robot::Robot()
{
	playerClient = new PlayerClient("localhost", 6665);
	laserProxy = new LaserProxy(playerClient);
	position2dProxy = new Position2dProxy(playerClient);

	position2dProxy->SetMotorEnable(true);

}

void Robot::SetStartLocation(Coordinates* location) {
	_startLocation = location;

	do {
		position2dProxy->SetOdometry(_startLocation->X,_startLocation->Y,_startLocation->Yaw);
		playerClient->Read();
	} while (!ConvertionHandler::aboutEquals(position2dProxy->GetXPos(), _startLocation->X, 0.01)
	        || !ConvertionHandler::aboutEquals(position2dProxy->GetYPos(), _startLocation->Y, 0.01)
	        || !ConvertionHandler::aboutEquals(position2dProxy->GetYaw(), _startLocation->Yaw, degreesToRadians(0.5)));
}

Coordinates* Robot::GetRobotsPosition()
{
	double x = position2dProxy->GetXPos();
	double y = position2dProxy->GetYPos();
	double yaw = ConvertionHandler::makeAngleNormal(position2dProxy->GetYaw());


	Coordinates* position = new Coordinates(x,y,yaw);

	return position;
}


void Robot::Read() {
	playerClient->Read();
}

void Robot::setSpeed(double forward_CmPerSec, double angular_RadiansPerSec) {
	position2dProxy->SetSpeed(cm_to_m(forward_CmPerSec), angular_RadiansPerSec);
}

double Robot::index_to_deg(int index) {
	double angular_resolution = LASER_FOV_DEGREE / (double) LASER_SAMPLES;
	double min_angle = LASER_FOV_DEGREE / 2;

	double angle = index * angular_resolution - min_angle;
	return angle;
}

unsigned Robot::deg_to_index(double degree) {
	double min_angle = LASER_FOV_DEGREE / 2;

	int index = ((double) LASER_SAMPLES / LASER_FOV_DEGREE) * (degree + min_angle);
	if ((unsigned) index >= LASER_SAMPLES) {
		throw new out_of_range("index not in range of scanner.");
	}

	return index;
}

vector<float> Robot::getLaserScan()
{
	vector<float> scans;
	scans.push_back(laserProxy->GetRange(333));
//
//	for (unsigned int i = 0; i < laserProxy->GetCount(); i++)
//	{
//		scans.push_back((*laserProxy)[i]);
//	}
	return scans;
}
