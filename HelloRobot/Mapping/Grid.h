/*
 * Grid.h
 *
 *  Created on: Jul 18, 2015
 *      Author: colman
 */

#ifndef GRID_H_
#define GRID_H_
#include "../Mapping/Cell.h"

namespace Mapping {

class Grid {
public:
	Grid();
	virtual ~Grid();
	vector<vector<Cell*> > Cells;
	unsigned RowsCount;
	unsigned ColumnsCount;
};

} /* namespace Path */

#endif /* GRID_H_ */
