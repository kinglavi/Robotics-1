/*
 * ConfigurationManager.h
 *
 *  Created on: Jul 16, 2015
 *      Author: colman
 */

#ifndef CONFIGURATIONMANAGER_H_
#define CONFIGURATIONMANAGER_H_
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string.h>
#include <fstream>
#include "../Mapping/Map.h"
#include "../Robot.h"

using namespace std;
using namespace Mapping;

namespace Common {

class ConfigurationManager {
public:
	virtual ~ConfigurationManager();
	static ConfigurationManager* Instance();

	// Goal
	int GetGoalX(){return Goal_X;}
	int GetGoalY(){return Goal_Y;}

	Robot* GetRobot(){return robot;}
	Map* GetMap(){return map;}

	void ReadFile(string path);
	void ParseLine(string line);

private:
	static ConfigurationManager* m_Config;
	ConfigurationManager();
	ConfigurationManager(const ConfigurationManager&) = delete;
	ConfigurationManager& operator=(const ConfigurationManager&) = delete;

	// Goal
	int Goal_X;
	int Goal_Y;

	// Start Location
	int Start_X;
	int Start_Y;
	double Start_Yaw;

	Robot* robot;
	Map* map;

	int str2int(const char* str, int h);

};

} /* namespace Common */

#endif /* CONFIGURATIONMANAGER_H_ */
