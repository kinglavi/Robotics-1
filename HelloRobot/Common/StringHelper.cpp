/*
 * StringHelper.cpp
 *
 *  Created on: Jul 18, 2015
 *      Author: colman
 */

#include "StringHelper.h"
#include <sstream>
#include <string>

using namespace std;

namespace Common {

StringHelper::StringHelper(){}

char* StringHelper::ConvertStringToCharArray(string string)
{
	char converted[1024];
	strncpy(converted, string.c_str(), sizeof(converted));
	converted[sizeof(converted) - 1] = 0;
	return converted;
}

} /* namespace Common */
