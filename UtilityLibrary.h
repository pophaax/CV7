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
<<<<<<< HEAD
=======

>>>>>>> branch 'master' of https://github.com/pophaax/CV7
class UtilityLibrary {
public:
<<<<<<< HEAD
	static std::vector<float> fixAngles(std::vector<float> v);
	static float getMeanValue(std::vector<float> v);
=======
	static float getMeanValue(std::vector<float> *v);
>>>>>>> branch 'master' of https://github.com/pophaax/CV7
	static float getMedianValue(std::vector<float> v);
	static std::map<std::string,float> parseString(char* buffer);
};

#endif /* CV7_UTILITYLIBRARY_H_ */
