#include "Coordinates.h"

#include <iostream>
#include <math.h>

#include "../Common/ConvertionHandler.h"

using namespace std;

namespace Mapping {

	Coordinates::Coordinates() :
			X(0), Y(0), Yaw(0) {
	}

	// In CM
	Coordinates::Coordinates(double x, double y, double yaw) {
		X = x;
		Y = y;
		Yaw = yaw;
	}

	ostream& operator<<(ostream& os, Coordinates& coordinate) {
		if (coordinate.X == INFINITY || coordinate.Y == INFINITY || coordinate.Yaw == INFINITY) {
			os << "infinity";
			return os;
		}

		os << "(" << cm_to_m(coordinate.X) << ", " << cm_to_m(coordinate.Y) << ", " << radiansToDegrees(coordinate.Yaw) << "(m, deg))";
		return os;
	}
}
