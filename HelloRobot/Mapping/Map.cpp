/*
 * Map.cpp
 *
 *  Created on: Jun 16, 2015
 *      Author: colman
 */

#include "Map.h"
#include <vector>

Map::Map() {}

double Map::Map_X_Cm()
{
	return (X_Pixles * Cm_To_Pixel_Ratio);
}

double Map::Map_Y_Cm()
{
	return (Y_Pixles * Cm_To_Pixel_Ratio);
}

