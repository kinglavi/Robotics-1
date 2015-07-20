/*
 * ConfigurationManager.cpp
 *
 *  Created on: Jul 16, 2015
 *      Author: colman
 */

#include "ConfigurationManager.h"
#include "StringHelper.h"
#include <sstream>
#include <string>

namespace Common {

ConfigurationManager* ConfigurationManager::m_Config = NULL;

ConfigurationManager::ConfigurationManager() {
	map = new Map();
	robot = new Robot();
	ReadFile("/home/colman/Desktop/proj/Robotics/HelloRobot/configuration.txt");
}

ConfigurationManager::~ConfigurationManager() {
	delete m_Config;
	m_Config = NULL;
}
ConfigurationManager* ConfigurationManager::Instance() {
	if (!m_Config) {
		m_Config = new ConfigurationManager();
	}

	return m_Config;
}

void ConfigurationManager::ReadFile(string path)
{
	string line;
	ifstream myfile (StringHelper::ConvertStringToCharArray(path));

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

	if(key == "map")
	{
		map->Map_Path = value;
		map->Map_Directory = value.substr(0, value.find_last_of('/'));
	}
	else if(key == "startLocation")
	{
		delimiter = " ";
		int accurance = value.find(delimiter);
		double Start_X = atoi(value.substr(0, accurance).c_str());
		value.erase(0, value.find(delimiter) + 1);
		accurance = value.find(delimiter);
		double Start_Y = atoi(value.substr(0, accurance).c_str());
		value.erase(0, accurance + 1);
		double Start_Yaw = atoi(value.substr(0, value.find(delimiter)).c_str());
		robot->SetStartLocation(new Coordinates(Start_X, Start_Y, Start_Yaw));
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
} /* namespace Common */
