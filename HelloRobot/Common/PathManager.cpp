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
	//_path = path;
	vector<Coordinates*> _path2;
	for(int i=0; i < path.size(); i++)
	{
		_path2.push_back(ConvertionHandler::getCoordinateInCm(path[i]));
	}
	_path = _path2;

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
