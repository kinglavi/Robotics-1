/*
 * AStar.h
 *
 *  Created on: Jun 2, 2015
 *      Author: colman
 */

#ifndef ASTAR_H_
#define ASTAR_H_
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string.h>
#include <fstream>
using namespace std;
#include "../Mapping/Cell.h"
#include "../Mapping/Grid.h"
using namespace Mapping;

class A_Star {
public:
	A_Star();
	virtual ~A_Star();
	static string pathFind(Cell* startCell, Cell* finishCell);
};

#endif /* ASTAR_H_ */
