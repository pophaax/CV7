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

using namespace std;

vector<float> UtilityLibrary::fixAngles(vector<float> v){
	unsigned int counter = 0;
	for (float f : v) {
		if (f < 90 || f > 270) {
			counter++;
		}
	}
	if (counter > (v.size()/2)) {
		vector<float> newV(v);
		for (float& f : newV) {
			if (f > 180 && f < 360) {
				f -= 360;
			}
		}
		return newV;
	}
	return v;
}

float UtilityLibrary::getMeanValue(vector<float> v)
{
	if(v.empty()) {
		return 0;
	}
	vector<float> fixedV = UtilityLibrary::fixAngles(v);

	float sum = 0;
	for(unsigned int i = 0; i < fixedV.size(); i++) {
		sum += fixedV.at(i);
	}
	float averageValue = sum/fixedV.size();
	if(averageValue < 0 ){
		averageValue+=360;
	}
	return averageValue;
}

float UtilityLibrary::getMedianValue(std::vector<float> v) {
	if(v.empty()) {
		return 0;
	}
	vector<float> fixedV = UtilityLibrary::fixAngles(v);
	sort(fixedV.begin(), fixedV.begin() + fixedV.size());
	unsigned int middle = (int) fixedV.size()/2;
	float middleValue = 0;
	if (fixedV.size() % 2 == 1) {
		middleValue = fixedV.at(middle);
	}
	else {
		if (fixedV.size() > middle) {
			middleValue = (fixedV.at(middle-1) + fixedV.at(middle)) / 2;
		}
		else {
			middleValue = fixedV.at(middle);
		}
	}
	if(middleValue < 0 ){
		middleValue+=360;
	}
	return middleValue;
}

std::map<std::string,float> UtilityLibrary::parseString(char* buffer) {
	float windDirection = 0;
	float windSpeed = 0;
	float windTemperature = 0;
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
	if (updated[IIMWV] == false || updated[WIXDR] == false ) {
		throw "UtilLibrary::parseString exception";
	}
	std::map<std::string,float> result;
	result.insert(std::make_pair("windDirection", windDirection));
	result.insert(std::make_pair("windSpeed",windSpeed) );
	result.insert(std::make_pair("windTemperature",windTemperature) );
	return result;
}
