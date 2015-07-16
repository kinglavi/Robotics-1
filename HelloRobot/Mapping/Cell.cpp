#include "Cell.h"

#include <float.h>
#include "../Common/ConfigurationManager.h"
using namespace std;
using namespace Common;

namespace Mapping {

	const unsigned Cell::NUM_NEIGHBORS = 8;
	const double Cell::COST_UNWALKABLE = DBL_MAX;
	const double Cell::COST_CLEAR = 1;
	const double Cell::COST_NEAR_WALL_LAYER1 = 7;
	const double Cell::COST_NEAR_WALL_LAYER2 = 6;
	const double Cell::COST_NEAR_WALL_LAYER3 = 5;
	const double Cell::COST_NEAR_WALL_LAYER4 = 4;
	const double Cell::COST_NEAR_WALL_LAYER5 = 3;

	Cell::Cell(unsigned x, unsigned y, double cost) {
		m_Col = x;
		m_Row = y;
		m_Cost = cost;
	}

	Cell::Cell(const Cell& cell) {
		m_Neighbors = cell.m_Neighbors;
		m_Col = cell.m_Col;
		m_Row = cell.m_Row;
		m_Cost = cell.m_Cost;
	}

	bool Cell::isWalkable() const {
		return m_Cost != Cell::COST_UNWALKABLE;
	}

	bool Cell::isClear() const {
		return m_Cost == Cell::COST_CLEAR;
	}

	Cell& Cell::operator=(const Cell& cell) {
		m_Neighbors = cell.m_Neighbors;
		m_Col = cell.m_Col;
		m_Row = cell.m_Row;
		m_Cost = cell.m_Cost;

		return *this;
	}

	ostream& operator<<(ostream& os, Cell* cell) {
		os << "[" << cell->getCol() << "," << cell->getRow() << "]";
		return os;
	}

	Coordinates* Cell::getWorldLocationCm() const {
		int resolution = ConfigurationManager::getConfig()->GetMap()->GridResolutionCM;
		double x_cm = m_Col * resolution;
		double y_cm = m_Row * resolution;

		Coordinates* coordinate = new Coordinates( x_cm, y_cm, 0);
		return coordinate;
	}

}
