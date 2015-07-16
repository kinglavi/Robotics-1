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
	static int Start_X;
	static int Start_Y;
	static int Start_Yaw;

	// Goal
	static int Goal_X;
	static int Goal_Y;

	static Robot* robot;
	static Map* map;

	static void ReadFile(string path);
	static void ParseLine(string line);
	static char* ConvertStringToCharArray(string string);
private:
	int str2int(const char* str, int h);

};

#endif /* CONFIGURATIONMANAGER_H_ */
