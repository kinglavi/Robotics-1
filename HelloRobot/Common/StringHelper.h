/*
 * StringHelper.h
 *
 *  Created on: Jul 18, 2015
 *      Author: colman
 */

#ifndef STRINGHELPER_H_
#define STRINGHELPER_H_

#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string.h>
#include <fstream>

using namespace std;

namespace Common {

class StringHelper {
public:
	StringHelper();
	static char* ConvertStringToCharArray(string string);
};

} /* namespace Common */

#endif /* STRINGHELPER_H_ */
