/*
 * main.cpp
 *
 *  Created on: Jan 10, 2015
 *      Author: colman
 */

#include <libplayerc++/playerc++.h>
#include "MovementManager.h"

int main() {
	MovementManager* a = new MovementManager();
	while (true) {
		a->pc.Read();

/*
		if(manager.GetRelativePrespective(manager.lp))
			pp.SetSpeed(0.0,0.3);
		else
			pp.SetSpeed(0.8,0.0);*/
	}

	return 0;
}

