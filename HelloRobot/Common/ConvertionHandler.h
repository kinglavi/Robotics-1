#pragma once

#include <math.h>
#include <float.h>

#define degreesToRadians(angleDegrees) (angleDegrees * M_PI / 180.0)
#define radiansToDegrees(angleRadians) (angleRadians * 180.0 / M_PI)

#define m_to_cm(m) (m * 100)
#define cm_to_m(cm) (0.01 * cm)

class ConvertionHandler {
	public:
		static bool isInRange(double number, double rangeStart, double rangeEnd, bool inclusive = true);
		static double distance(double deltaX, double deltaY);
		static double distance(double x1, double y1, double x2, double y2);
		static double normalize(double number, double minValue = DBL_MIN, double maxValue = DBL_MAX);
		static bool aboutEquals(double number, double comparee, double epsilon = DBL_EPSILON);
		static double angleBetweenPointsDeg(double x1, double y1, double x2, double y2);
		static double floorRound(double x, int precisionValue = 10000);
		static float normalPdf(float x, float median, float s_dev);
};
