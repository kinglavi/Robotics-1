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
#include "../Robot.h"
#include "../Mapping/Map.h"
using namespace std;

namespace Common {

class ConfigurationManager {
public:
	virtual ~ConfigurationManager();
	static ConfigurationManager* getConfig();

	// Start Location
	int GetStartX(){return Start_X;}
	int GetStartY(){return Start_Y;}
	int GetStartYaw(){return Start_Yaw;}

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

	// Start Location
	int Start_X;
	int Start_Y;
	int Start_Yaw;

	// Goal
	int Goal_X;
	int Goal_Y;

	Robot* robot;
	Map* map;

	int str2int(const char* str, int h);
	char* ConvertStringToCharArray(string string);
};

} /* namespace Common */

#endif /* CONFIGURATIONMANAGER_H_ */
