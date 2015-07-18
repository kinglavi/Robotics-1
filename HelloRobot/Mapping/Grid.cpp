/*
 * Grid.cpp
 *
 *  Created on: Jul 18, 2015
 *      Author: colman
 */

#include "Grid.h"
#include "../Common/ConfigurationManager.h"
using namespace Common;

namespace Mapping {

Grid::Grid() {
	// TODO Auto-generated constructor stub
	double width = ConfigurationManager::getConfig()->GetMap()->Map_X_Cm();
	double height = ConfigurationManager::getConfig()->GetMap()->Map_Y_Cm();
	double CmsToCell =ConfigurationManager::getConfig()->GetMap()->GridResolutionCM;
	RowsCount = height/CmsToCell;
	ColumnsCount = width/CmsToCell;
	Cells.resize(RowsCount);
	for (unsigned i = 0; i < RowsCount; i++) {
		Cells[i].resize(ColumnsCount);
		for (unsigned j = 0; j < ColumnsCount; j++) {
			// Initialize cells
			Cells[i][j] = new Cell(j, i);
		}
	}
}

Grid::~Grid() {
	// TODO Auto-generated destructor stub
}

} /* namespace Path */
