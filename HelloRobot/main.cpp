/*
 * main.cpp
 *
 *  Created on: Jan 10, 2015
 *      Author: colman
 */

#include <libplayerc++/playerc++.h>
#include "MovementManager.h"

int main() {
	MovementManager* manager = new MovementManager();
	while (true) {
		manager->pc->Read();


		if(manager->GetRelativePrespective())
			manager->pp->SetSpeed(0.0,0.3);
		else
			manager->pp->SetSpeed(0.8,0.0);

		manager->GetRobotsPosition();
	}

	return 0;
}

