#pragma once

#include <string>

namespace PlayerCc {
	class Position2dProxy;
};

using namespace std;
using namespace PlayerCc;

class PositionHandler {
	public:
		static string getPositionString(Position2dProxy* positionProxy);
};
