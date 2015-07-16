#include "PositionHandler.h"

#include <string>
#include <sstream>
#include <iostream>
#include <libplayerc++/playerc++.h>

#include "ConvertionHandler.h"

using namespace std;
using namespace PlayerCc;

string PositionHandler::getPositionString(Position2dProxy* positionProxy) {
	double x = positionProxy->GetXPos();
	double y = positionProxy->GetYPos();
	double yawRad = positionProxy->GetYaw();

	std::stringstream ss;
	ss << "(" << x << ", " << y << ", " << radiansToDegrees(yawRad) << ")";

	return ss.str();
}
