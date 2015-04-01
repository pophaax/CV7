/*
 * UtilityLibrary.cpp
 *
 *  Created on: Mar 31, 2015
 *      Author: sailbot
 */
#include <vector>
#include <iostream>
#include "UtilityLibrary.h"

float UtilityLibrary::getAverageValue(vector<float> *v)
{
	if(v->empty()) {
		return 0;
	}

	float sum = 0;
	for(unsigned int i = 0; i < v->size(); i++) {
		sum += v->at(i);
	}
	float averageValue = sum/v->size();
	return averageValue;
}

float UtilityLibrary::getMiddleValue(vector<float> *v) {
	if(v->empty()) {
		return 0;
	}
	unsigned int middle = (int)v->size()/2;
	if (v->size() % 2 == 1) {
		return v->at(middle);
	}
	else {
		if (v->size() > middle) {
			return (v->at(middle-1) + v->at(middle)) / 2;
		}
		else {
			return v->at(middle);
		}
	}
}
