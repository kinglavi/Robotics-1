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
	Grid(unsigned rows, unsigned columns);
	virtual ~Grid();
	Cell*** Cells;
	unsigned RowsCount;
	unsigned ColumnsCount;
};

} /* namespace Path */

#endif /* GRID_H_ */
