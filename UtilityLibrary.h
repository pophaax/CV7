/*
 * UtilityLibrary.h
 *
 *  Created on: Mar 31, 2015
 *      Author: sailbot
 */

#ifndef CV7_UTILITYLIBRARY_H_
#define CV7_UTILITYLIBRARY_H_
#include <vector>
#include <map>
#include <string.h>
#include <stdlib.h>

class UtilityLibrary {
public:
	static std::vector<float> fixAngles(std::vector<float> v);
	static float getMeanValue(std::vector<float> v);
	static float getMedianValue(std::vector<float> v);
	static std::map<std::string,float> parseString(char* buffer);
};

#endif /* CV7_UTILITYLIBRARY_H_ */
