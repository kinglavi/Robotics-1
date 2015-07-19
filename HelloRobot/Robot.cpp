/*
 * Robot.cpp
 *
 *  Created on: Jun 16, 2015
 *      Author: colman
 */

#include "Robot.h"

	const unsigned LASER_SAMPLES = 666;
	const double LASER_FOV_DEGREE = 240.0;

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

float* Robot::getLaserScan()
{
	float *scan = new float[_lp.GetCount()];
	for (unsigned int i = 0; i < _lp.GetCount(); i++)
	{
		scan[i] = _lp[i];
	}
	return scan;
}
