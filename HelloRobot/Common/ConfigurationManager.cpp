/*
 * ConfigurationManager.cpp
 *
 *  Created on: Jun 16, 2015
 *      Author: colman
 */

#include "ConfigurationManager.h"

ConfigurationManager::ConfigurationManager()
{
	map = new Map();
	robot = new Robot();
	ReadFile("/home/colman/Desktop/Robotics/Robotics/HelloRobot/configuration.txt");
}

char* ConfigurationManager::ConvertStringToCharArray(string string)
{
	char converted[1024];
	strncpy(converted, string.c_str(), sizeof(converted));
	converted[sizeof(converted) - 1] = 0;
	return converted;
}

void ConfigurationManager::ReadFile(string path)
{
	string line;
	ifstream myfile (ConvertStringToCharArray(path));

	if (myfile.is_open())
	{
		while (getline(myfile,line))
		{
			ParseLine(line);
		}

		myfile.close();
	}

	  else cout << "Unable to open file";
}

void ConfigurationManager::ParseLine(string line)
{
	string delimiter = ":";
	string key = line.substr(0, line.find(delimiter));
	string value = line.substr(line.find(delimiter) + 2, line.size());

	if(key == "Map")
	{
		map->Map_Path = value;
	}
	else if(key == "startLocation")
	{
		delimiter = " ";
		int accurance = value.find(delimiter);
		Start_X = atoi(value.substr(0, accurance).c_str());
		value.erase(0, value.find(delimiter) + 1);
		accurance = value.find(delimiter);
		Start_Y = atoi(value.substr(0, accurance).c_str());
		value.erase(0, accurance + 1);
		Start_Yaw = atoi(value.substr(0, value.find(delimiter)).c_str());

	}
	else if(key == "goal")
	{
		delimiter = " ";
		int accurance = value.find(delimiter);
		Goal_X = atoi(value.substr(0, accurance).c_str());
		value.erase(0, value.find(delimiter) + 1);
		accurance = value.find(delimiter);
		Goal_Y = atoi(value.substr(0, accurance).c_str());
	}
	else if(key == "robotSize")
	{
		delimiter = " ";
		int accurance = value.find(delimiter);
		robot->Height = atoi(value.substr(0, accurance).c_str());
		value.erase(0, value.find(delimiter) + 1);
		accurance = value.find(delimiter);
		robot->Width = atoi(value.substr(0, accurance).c_str());
	}
	else if(key == "MapResolutionCM")
	{
		map->Cm_To_Pixel_Ratio = atof(value.c_str());
	}
	else if(key == "GridResolutionCM")
	{
		map->GridResolutionCM = atof(value.c_str());
	}
}

