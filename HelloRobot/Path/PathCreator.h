/*
 * PathCreator.h
 *
 *  Created on: Jul 18, 2015
 *      Author: colman
 */

#ifndef PATHCREATOR_H_
#define PATHCREATOR_H_

#include <vector>
#include "../Mapping/Cell.h"
#include "../Mapping/Grid.h"
using namespace Mapping;

namespace Path {

class PathCreator {
public:
	PathCreator();
	virtual ~PathCreator();
	vector<Cell*> CreatePath(Grid* grid, Cell* start, Cell* dest);
	void PutWeights(Grid* grid);
};

} /* namespace Path */

#endif /* PATHCREATOR_H_ */
