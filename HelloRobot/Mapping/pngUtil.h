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
	// Consts
	#define R_OFFSET 0
	#define G_OFFSET 1
	#define B_OFFSET 2
	#define A_OFFSET 3

	static const unsigned COLOR_BLACK = 0;
	static const unsigned COLOR_WHITE = 255;
	static const int COLOR_INVALID = -1;

	void encodeOneStep(const char* filename, std::vector<unsigned char> image, unsigned width, unsigned height);
	void decodeOneStep(const char* filename);
	static unsigned char getPixelColor(const std::vector<unsigned char>& rawImage, unsigned width, unsigned height, unsigned row, unsigned col);
	void PadMap(const char* filename, unsigned paddingSize);
	void CreateGrid(unsigned paddingSize, int MapResolutionCM, int GridResolutionCM)
	private:
	bool IsInDistance(int firstX,int firsty,int secondX,int secondY, unsigned paddingSize);
};

