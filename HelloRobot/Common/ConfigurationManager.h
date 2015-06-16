/*
 * ConfigurationManager.h
 *
 *  Created on: Jun 16, 2015
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

class ConfigurationManager {
public:
	ConfigurationManager();
	// Start Location
	int Start_X;
	int Start_Y;
	int Start_Yaw;

	// Goal
	int Goal_X;
	int Goal_Y;

	Robot* robot;
	Map* map;

	void ReadFile(string path);
	void ParseLine(string line);
private:
	int str2int(const char* str, int h);
	char* ConvertStringToCharArray(string string);
};

#endif /* CONFIGURATIONMANAGER_H_ */
