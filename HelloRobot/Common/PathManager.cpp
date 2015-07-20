/*
 * PathManager.cpp
 *
 *  Created on: Jul 19, 2015
 *      Author: colman
 */

#include "PathManager.h"
#include "../Mapping/Cell.h"

namespace Common {

PathManager::PathManager(vector<Coordinates*> path) {
	// TODO Auto-generated constructor stub
	_path = path;

	// remove the first item because it's the robot's starting point
	_path.erase(_path.begin());
	_currentIndex = 0;
}

PathManager::~PathManager() {
	// TODO Auto-generated destructor stub
}

Coordinates* PathManager::GetNextCoordinateInPath() {
	return _path[_currentIndex];
}

bool PathManager::MoveToNextCoordinate(){
	_currentIndex++;
	return _currentIndex < _path.size();
}

} /* namespace Path */
