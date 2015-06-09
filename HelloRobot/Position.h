/*
 * Position.h
 *
 *  Created on: Jun 9, 2015
 *      Author: colman
 */

#ifndef POSITION_H_
#define POSITION_H_

class Position {
public:
	Position();
	Position(double x, double y, double yaw);

	double x;
	double y;
	double yaw;
};

#endif /* POSITION_H_ */
