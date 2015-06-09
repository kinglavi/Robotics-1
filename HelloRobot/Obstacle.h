/*
 * Obstacle.h
 *
 *  Created on: Jun 9, 2015
 *      Author: colman
 */

#ifndef OBSTACLE_H_
#define OBSTACLE_H_

class Obstacle {
public:
	Obstacle();
	Obstacle(double angle, double distance);

	double Angle;
	double Distance;
};

#endif /* OBSTACLE_H_ */
