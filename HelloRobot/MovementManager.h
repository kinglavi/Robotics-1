/*
 * MovementManager.h
 *
 *  Created on: Jun 2, 2015
 *      Author: colman
 */

#ifndef MOVEMENTMANAGER_H_
#define MOVEMENTMANAGER_H_

#include <libplayerc++/playerc++.h>

using namespace PlayerCc;

class MovementManager {
public:
	MovementManager();
	virtual ~MovementManager();
	bool GetRelativePrespective();

	PlayerClient* pc;
	LaserProxy* lp;
	Position2dProxy* pp;
};


#endif /* MOVEMENTMANAGER_H_ */
