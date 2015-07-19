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
	/* WAYPOINTS */
	const float RADIUS_AROUND_POINT_CM = 10.0;
	const unsigned MAX_WAYPOINT_SPACING = 10;

	PathCreator();
	virtual ~PathCreator();
	vector<Cell*> CreatePath(Cell* start, Cell* dest);

private:
	void PutWeights();
<<<<<<< HEAD
	vector<Cell*> RunAStar(Cell* start, Cell* end);
	vector<Coordinates> SmoothPath(vector<Cell*> cellsPath, Coordinates start, Coordinates end);
	bool IsStraitApprocah(Coordinates firstWorldLocationCm, Coordinates secondWorldLocationCm);
=======
	bool IsStraitApprocah(Coordinates* firstWorldLocationCm, Coordinates* secondWorldLocationCm);
	vector<Coordinates*> GetFinalPath(Cell* start, Cell* dest);
>>>>>>> branch 'master' of https://github.com/mkobi/Robotics.git
};

} /* namespace Path */

#endif /* PATHCREATOR_H_ */
