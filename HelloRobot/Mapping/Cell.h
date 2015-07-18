#pragma once

#include <iostream>
#include <vector>

#include "../Common/ConfigurationManager.h"
#include "Coordinates.h"

using namespace std;

namespace Mapping {

	class Cell {
		public:
			static const double COST_UNWALKABLE;
			static const double COST_CLEAR;
			static const double COST_NEAR_WALL_LAYER1;
			static const double COST_NEAR_WALL_LAYER2;
			static const double COST_NEAR_WALL_LAYER3;
			static const double COST_NEAR_WALL_LAYER4;
			static const double COST_NEAR_WALL_LAYER5;
			static const double NUM_OF_LAYERS;
			static const unsigned NUM_NEIGHBORS;

			Cell(unsigned col, unsigned row, double cost = COST_CLEAR);
			Cell(const Cell& cell);
			virtual ~Cell() {}

			inline void setNeighbors(vector<Cell*> neighbors) { m_Neighbors = neighbors; }
			inline vector<Cell*> getNeighbors() const { return m_Neighbors; }
			inline unsigned getCol() const { return m_Col; }
			inline unsigned getRow() const { return m_Row; }
			inline double getCost() const { return m_Cost; }
			inline void setCost(double cost) { m_Cost = cost; }

			Coordinates* getWorldLocationCm() const;
			bool isWalkable() const;
			bool isClear() const;

			Cell& operator=(const Cell& cell);
			friend ostream& operator<<(ostream& os, Cell* cell);
		protected:
			vector<Cell*> m_Neighbors;
			unsigned m_Col;
			unsigned m_Row;
			double m_Cost;
	};

}
