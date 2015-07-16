#pragma once

#include <iostream>

using namespace std;

namespace Mapping{

	class Coordinates {
		public:
			double X;
			double Y;
			double Yaw;

			Coordinates();
			Coordinates(double xCM, double yCM, double yawRad);

			friend ostream& operator<<(ostream& os, Coordinates& coordinates);
	};

}
