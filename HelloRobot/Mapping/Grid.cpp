/*
 * Grid.cpp
 *
 *  Created on: Jul 18, 2015
 *      Author: colman
 */

#include "Grid.h"

namespace Mapping {

Grid::Grid(unsigned rows, unsigned columns) {
	// TODO Auto-generated constructor stub
	Cells = new Cell**[rows];
	for(int i = 0; i < rows; ++i)
		Cells[i] = new Cell*[columns];
}

Grid::~Grid() {
	// TODO Auto-generated destructor stub
}

} /* namespace Path */
