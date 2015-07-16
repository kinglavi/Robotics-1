#pragma once

#include <iostream>

using namespace std;

namespace model {

	class Coordinates {
		public:
			double X; // CM
			double Y; // CM
			double Yaw; // RAD

			Coordinates();
			Coordinates(double xCM, double yCM, double yawRad);

			friend ostream& operator<<(ostream& os, Coordinates& coordinates);
	};

}
