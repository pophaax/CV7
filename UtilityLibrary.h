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

	// new mean function without fixAngles
	static float mean(std::vector<float> values);
	static float meanOfAngles(std::vector<float> anglesInDegrees);
	
	/*
	 * Converts an angle in degrees to cartesian coordinates (x,y) on the
	 * unit circle
	 */
	static void polarToCartesian(float degrees, float& x, float& y);

	static std::map<std::string,float> parseString(const char* buffer);
};

#endif /* CV7_UTILITYLIBRARY_H_ */
