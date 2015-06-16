/*
 * Map.h
 *
 *  Created on: Jun 16, 2015
 *      Author: colman
 */

#ifndef MAP_H_
#define MAP_H_
#include "pngUtil.h"

using namespace std;

class Map {
public:
	Map();
	string Map_Path;
	int X_Pixles;
	int Y_Pixles;
	double Cm_To_Pixel_Ratio;
	int GridResolutionCM;

	double Map_X_Cm();
	double Map_Y_Cm();
	vector<unsigned char> image;

};

#endif /* MAP_H_ */
