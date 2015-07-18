#pragma once

#include <iostream>
#include <vector>
#include <math.h>
#include <string.h>
#include "../Common/ConfigurationManager.h"
#include "../Common/StringHelper.h"
using namespace std;

class pngUtil {
	public:
	static const unsigned COLOR_BLACK = 0;
	static const unsigned COLOR_WHITE = 255;
	static const int COLOR_INVALID = -1;

	static void encodeOneStep(const char* filename, std::vector<unsigned char> image, unsigned width, unsigned height);
	static void decodeOneStep(const char* filename);
	static unsigned char getPixelColor(const std::vector<unsigned char>& rawImage, unsigned width, unsigned height, unsigned row, unsigned col);
	static char* PadMap(const char* filename, unsigned paddingSize);
	static bool IsInDistance(int firstX,int firsty,int secondX,int secondY, unsigned paddingSize);

};

