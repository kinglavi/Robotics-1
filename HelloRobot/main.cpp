/*
 * main.cpp
 *
 *  Created on: Jan 10, 2015
 *      Author: colman
 */

#include <libplayerc++/playerc++.h>
#include "Common/MovementManager.h"
#include "Mapping/pngUtil.h"
#include "Common/ConfigurationManager.h"

int main() {
	pngUtil* util = new pngUtil();
	const char* filename = "/home/colman/Desktop/Robotics/Robotics/HelloRobot/roboticLabMap.png";
	util->PadMap(filename, 5);

	MovementManager* manager = new MovementManager();

	vector<Obstacle*> obs = manager->GetRelativePrespective();
	vector<Obstacle*>::iterator i;

	for(i=obs.begin(); i!=obs.end(); i++)
	{
		cout << "Angle: " << (*i)->Angle << ", Distance: " << (*i)->Distance << endl;
	}

	while (true) {
		manager->pc->Read();


/*		if(manager->GetRelativePrespective())
			manager->pp->SetSpeed(0.0,0.3);
		else
			manager->pp->SetSpeed(0.8,0.0);*/

		manager->GetRobotsPosition();
	}

	return 0;
}

