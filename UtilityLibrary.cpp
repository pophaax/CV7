/*
 * UtilityLibrary.cpp
 *
 *  Created on: Mar 31, 2015
 *      Author: sailbot
 */
#include <vector>
#include <map>
#include <iostream>
#include <algorithm>
#include "UtilityLibrary.h"

float UtilityLibrary::getMeanValue(std::vector<float> *v)
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

float UtilityLibrary::getMedianValue(std::vector<float> v) {
	if(v.empty()) {
		return 0;
	}
	sort(v.begin(), v.begin() + v.size());
	unsigned int middle = (int) v.size()/2;
	if (v.size() % 2 == 1) {
		return v.at(middle);
	}
	else {
		if (v.size() > middle) {
			return (v.at(middle-1) + v.at(middle)) / 2;
		}
		else {
			return v.at(middle);
		}
	}
}

std::map<std::string,float> UtilityLibrary::parseString(char* buffer) {
	float windDirection;
	float windSpeed;
	float windTemperature;
	const int IIMWV = 0;
	const int WIXDR = 1;
	bool updated[] = { false, false };

	char* split = strtok(buffer, "$,");

	while (split != NULL) {
		if (strcmp(split, "IIMWV") == 0) {
			split = strtok(NULL, "$,");
			windDirection = atof(split);
			split = strtok(NULL, "$,");
			split = strtok(NULL, "$,");
			windSpeed = atof(split);
			updated[IIMWV] = true;
		} else if (strcmp(split, "WIXDR") == 0) {
			split = strtok(NULL, "$,");
			split = strtok(NULL, "$,");
			windTemperature = atof(split);
			updated[WIXDR] = true;
		}

		if (updated[IIMWV] && updated[WIXDR]) {
			break;
		}
		split = strtok(NULL, "$,");
	}
	std::map<std::string,float> result;
	result.insert(std::make_pair("windDirection", windDirection));
	result.insert(std::make_pair("windSpeed",windSpeed) );
	result.insert(std::make_pair("windTemperature",windTemperature) );
	return result;
}
