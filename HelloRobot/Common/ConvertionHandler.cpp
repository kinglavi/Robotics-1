#include "ConvertionHandler.h"
#include <math.h>

using namespace std;

bool ConvertionHandler::isInRange(double number, double rangeStart, double rangeEnd, bool inclusive) {
	if (inclusive) {
		return number >= rangeStart && number <= rangeEnd;
	} else {
		return number > rangeStart && number < rangeEnd;
	}
}

double ConvertionHandler::distance(double deltaX, double deltaY) {
	return sqrt(pow(deltaX, 2) + pow(deltaY, 2));
}

double ConvertionHandler::distance(double x1, double y1, double x2, double y2) {
	return distance(x2 - x1, y2 - y1);
}

double ConvertionHandler::normalize(double number, double minValue, double maxValue) {
	if (isInRange(number, minValue, maxValue)) {
		return number;
	} else if (number < minValue) {
		return minValue;
	} else if (number > maxValue) {
		return maxValue;
	}

	return NAN;
}

bool ConvertionHandler::aboutEquals(double number, double comparee, double epsilon) {
	return isInRange(number, comparee - epsilon, comparee + epsilon);
}

double ConvertionHandler::angleBetweenPointsDeg(double x1, double y1, double x2, double y2) {
	double angleRad = atan2(y2 - y1, x2 - x1);
	if (angleRad < 0) {
		angleRad += 2 * M_PI;
	}

	return radiansToDegrees(angleRad);
}

double ConvertionHandler::floorRound(double x, int precisionValue) {
	return floor(precisionValue * x) / precisionValue;
}

float ConvertionHandler::normalPdf(float x, float median, float s_dev) {
	static const float inv_sqrt_2pi = 0.3989422804014327;
	float a = (x - median) / s_dev;

	return inv_sqrt_2pi / s_dev * exp(-0.5f * a * a);
}

double ConvertionHandler::makeAngleNormal(double angle){
	while (angle < 0)
	{
		angle = ConvertionHandler::floorRound(angle + 2 * M_PI);
	}

	while (angle > 2*M_PI)
	{
		angle = ConvertionHandler::floorRound(angle - 2 * M_PI);
	}

	return angle;
}

Coordinates* ConvertionHandler::getCoordinateInCm(Coordinates* coordinate) {
	Coordinates* coord = new Coordinates();
	coord->X = cm_to_m(coordinate->X);
	coord->Y = -1 * cm_to_m(coordinate->Y);
	return coord;
}


