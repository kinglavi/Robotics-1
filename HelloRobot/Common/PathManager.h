/*
 * PathManager.h
 *
 *  Created on: Jul 19, 2015
 *      Author: colman
 */

#ifndef PATHMANAGER_H_
#define PATHMANAGER_H_
#include "../Mapping/Coordinates.h"
#include "../Common/ConvertionHandler.h"
#include <vector>

using namespace Mapping;

namespace Common {

class PathManager {
public:
	PathManager(vector<Coordinates*> path);
	virtual ~PathManager();

	Coordinates* GetNextCoordinateInPath();
	bool MoveToNextCoordinate();
private:
	vector<Coordinates*> _path;
	int _currentIndex;
};

} /* namespace Path */

#endif /* PATHMANAGER_H_ */
