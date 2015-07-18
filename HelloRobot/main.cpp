/*
 * main.cpp
 *
 *  Created on: Jan 10, 2015
 *      Author: colman
 */

#include <libplayerc++/playerc++.h>
#include "Common/MovementManager.h"
#include "Mapping/pngUtil.h"
#include "Common/StringHelper.h"
#include "Common/ConfigurationManager.h"
using namespace Common;

int main() {
	pngUtil* util = new pngUtil();
	double gridRes = ConfigurationManager::getConfig()->GetMap()->GridResolutionCM;
	double mapRes = ConfigurationManager::getConfig()->GetMap()->Cm_To_Pixel_Ratio;
	double robotSize = ConfigurationManager::getConfig()->GetRobot()->Width;
	string path = ConfigurationManager::getConfig()->GetMap()->Map_Path;
	const char* filename = StringHelper::ConvertStringToCharArray(path);

	util->CreateGrid(filename, (1/mapRes)*(robotSize/2), mapRes, gridRes);

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

