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
	static const unsigned IMAGE_COLOR_CLEAR = 255; // WHITE
	static const unsigned IMAGE_COLOR_OBSTACLE = 0; // BLACK

	Map();
	string Map_Path;
	int X_Pixles;
	int Y_Pixles;
	double Cm_To_Pixel_Ratio;
	int GridResolutionCM;

	double Map_X_Cm();
	double Map_Y_Cm();
	vector<unsigned char> image;

	// Utility Methods
	unsigned getCellImageColor(unsigned row, unsigned col,
			const vector<unsigned char>& rawImage,
			unsigned imageWidth, unsigned imageHeight,
	        unsigned pixelsPerOneGrid);
};

#endif /* MAP_H_ */
