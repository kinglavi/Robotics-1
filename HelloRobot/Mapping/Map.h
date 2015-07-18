#ifndef MAP_H_
#define MAP_H_
#include "loadpng.h"
#include "pngUtil.h"
#include "../Mapping/Cell.h"

using namespace std;
namespace Mapping{
class Cell;
class Map {

public:
	// Consts
	#define R_OFFSET 0
	#define G_OFFSET 1
	#define B_OFFSET 2
	#define A_OFFSET 3

	static const unsigned COLOR_BLACK = 0;
	static const unsigned COLOR_WHITE = 255;
	static const int COLOR_INVALID = -1;

	static const unsigned IMAGE_COLOR_CLEAR = 255; // WHITE
	static const unsigned IMAGE_COLOR_OBSTACLE = 0; // BLACK

	Map();
	Map(const Map& map);
	Map(unsigned height, unsigned width);
	string Map_Path;
	string Map_Directory;
	int X_Pixles;
	int Y_Pixles;
	int Grid_Height;
	int Grid_Width;
	double Cm_To_Pixel_Ratio;
	int GridResolutionCM;

	double Map_X_Cm();
	double Map_Y_Cm();
	vector<unsigned char> image;
	void CreateGrid(unsigned paddingSize);
	void Initialize(unsigned height, unsigned width);
	vector<vector<Cell*> > Grid;
	vector<vector<char> > GridChar;
	Cell* operator()(int row, int col) const;

	Cell* getCell(int row, int col) const;
	Cell* getCellFromLocation(int row, int col) const;
	bool isInRange(int row, int col) const;
	void PrintGrid();
	private:
	// Utility Methods
	static unsigned getCellImageColor(unsigned row, unsigned col,
			const vector<unsigned char>& rawImage,
			unsigned imageWidth, unsigned imageHeight,
			unsigned pixelsPerOneGrid);


};
}
#endif /* MAP_H_ */
