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
#include <numeric>
#include "UtilityLibrary.h"

using namespace std;

bool IsOutOfRange (float f) {
	return (f < 90 || f > 270);
}

vector<float> UtilityLibrary::fixAngles(vector<float> v){
	unsigned int counter =  count_if(v.begin(), v.end(), IsOutOfRange);
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
	double sum = std::accumulate(fixedV.begin(), fixedV.end(), 0.0);
	double mean = sum / fixedV.size();
	if(mean < 0 ){
		mean+=360;
	}
	return mean;
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

float UtilityLibrary::mean(std::vector<float> values)
{
	float sum = 0;

	for(std::vector<float>::iterator it = values.begin();
		it != values.end(); ++it)
	{
		sum += *it;
	}

	return sum / values.size();
}

/*
 * uses formula for calculating mean of angles
 * https://en.wikipedia.org/wiki/Mean_of_circular_quantities
 */
float UtilityLibrary::meanOfAngles(std::vector<float> anglesInDegrees)
{
	std::vector<float> xx, yy;
	float x, y;

	// convert all angles to cartesian coordinates
	for(std::vector<float>::iterator it = anglesInDegrees.begin();
		it != anglesInDegrees.end(); ++it)
	{
		polarToCartesian(*it, x, y);
		xx.push_back(x);
		yy.push_back(y);
	}

	// use formula
	float meanAngleRadians = atan2(mean(yy), mean(xx));
	// atan2 produces results in the range (−π, π],
	// which can be mapped to [0, 2π) by adding 2π to negative results
	if (meanAngleRadians < 0) meanAngleRadians += 2*M_PI;
	
	return meanAngleRadians * 180/M_PI;
}

void UtilityLibrary::polarToCartesian(float degrees, float& x, float& y)
{
	x = cos(degrees * M_PI/180);
	y = sin(degrees * M_PI/180);
}

std::map<std::string,float> UtilityLibrary::parseString(const char* buffer) {
	float windDirection = 0;
	float windSpeed = 0;
	float windTemperature = 0;
	const int IIMWV = 0;
	const int WIXDR = 1;
	bool updated[] = { false, false };
	char * writalbeBuff;
	writalbeBuff = const_cast<char *>(buffer);
	char* split = strtok(writalbeBuff, "$,");

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
