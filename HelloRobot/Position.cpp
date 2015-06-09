/*
 * Position.cpp
 *
 *  Created on: Jun 9, 2015
 *      Author: colman
 */

#include "Position.h"

Position::Position() {}
Position::Position(double x, double y, double yaw)
{
	this->x = x;
	this->y = y;
	this->yaw = yaw;
}

