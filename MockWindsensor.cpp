/*
 * MockWindsensor.cpp
 *
 *  Created on: Apr 23, 2015
 *      Author: sailbot
 */

#include "CV7.h"
#include "MockWindsensor.h"

void MockWindsensor::loadConfig(std::string portName, int baudRate){

}

void MockWindsensor::setBufferSize(unsigned int bufferSize) {

}

void MockWindsensor::setBaudRate(unsigned int baudRate) {

}

void MockWindsensor::setPortName(std::string portName) {

}

unsigned int MockWindsensor::getBufferSize() {
	return 11;
}

void MockWindsensor::refreshData() {

}

bool MockWindsensor::isUseMean() {
	return true;
}

void MockWindsensor::setUseMean(bool useMean) {

}

float MockWindsensor::getDirection() {
	return 2.3;
}

float MockWindsensor::getSpeed() {
	return 21.5;
}

float MockWindsensor::getTemperature() {
	return 6.5;
}



