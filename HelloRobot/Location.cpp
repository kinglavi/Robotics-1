#include "Location.h"

namespace model {

	Location::Location() : Location(0,0,0) {
	}

	Location::Location(double x, double y, double yaw) {
		position_X = x;
		position_Y = y;
		position_Yaw = yaw;
	}

	Location::~Location() {

	}
}
