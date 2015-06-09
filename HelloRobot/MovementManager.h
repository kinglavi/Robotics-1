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
#include "Position.h"

using namespace PlayerCc;
using namespace std;

class MovementManager {
public:
	MovementManager();
	bool GetRelativePrespective();
	Position* GetRobotsPosition();
	double getAlpha();
	double getBeta();

	PlayerClient* pc;
	LaserProxy* lp;
	Position2dProxy* pp;
};


#endif /* MOVEMENTMANAGER_H_ */
