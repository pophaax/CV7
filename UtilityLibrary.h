/*
 * UtilityLibrary.h
 *
 *  Created on: Mar 31, 2015
 *      Author: sailbot
 */

#ifndef CV7_UTILITYLIBRARY_H_
#define CV7_UTILITYLIBRARY_H_
#include <vector>
#include <string>

using namespace std;
class UtilityLibrary {
public:
	static float getAverageValue(vector<float> *v);
	static float getMiddleValue(vector<float> *v);
};

#endif /* CV7_UTILITYLIBRARY_H_ */
