#include "CV7.h"
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <wiringSerial.h>
#include <iostream>


CV7::CV7() {
		m_bufferSize = 30;
		m_useMean = true;
}

CV7::~CV7() 
{
	if(m_fd < 0) {
		serialClose(m_fd);
	}
}

void CV7::loadConfig(std::string portName, int baudRate)
{	
	if((m_fd = serialOpen(portName.c_str(), baudRate)) < 0) {
		throw "CV7::openPort: Unable to connect";
	}
}

void CV7::setBufferSize(unsigned int bufferSize)
{
	if(bufferSize < 0)
	{
		throw "CV7::setBufferSize: bufferSize must be 1 or higher";
	}
	m_bufferSize = bufferSize;
}

unsigned int CV7::getBufferSize()
{
	return m_bufferSize;
}

void CV7::refreshData()
{
	const int NON_BREAKING_SPACE = 255;
	const int BUFF_SIZE = 256;
	char buffer[BUFF_SIZE];

	int index = 0;
	while(index < BUFF_SIZE) {

		buffer[index] = serialGetchar(m_fd);
		fflush(stdout);
		
		if(NON_BREAKING_SPACE == ((int)buffer[index])) {
			throw "CV7::refreshData: Serial read timeout";
		}
		
		index++;
	}
	std::map<std::string,float> result = UtilityLibrary::parseString(buffer);
	m_windDirection.push_back(result.find("windDirection")->second);
	m_windSpeed.push_back(result.find("windSpeed")->second);
	m_windTemperature.push_back(result.find("windTemperature")->second);

	while(m_windDirection.size() > m_bufferSize) {
		m_windDirection.erase(m_windDirection.begin());
		m_windSpeed.erase(m_windSpeed.begin());
		m_windTemperature.erase(m_windTemperature.begin());
	}
}

bool CV7::isUseMean() {
	return m_useMean;
}

void CV7::setUseMean(bool useMean) {
	m_useMean = useMean;
}

float CV7::getDirection()
{
	if (m_useMean) {
		return UtilityLibrary::getMeanValue(m_windDirection);
	}
	else {
		return UtilityLibrary::getMedianValue(m_windDirection);
	}
}

float CV7::getSpeed()
{
	if (m_useMean) {
		return UtilityLibrary::getMeanValue(m_windSpeed);
	}
	else {
		return UtilityLibrary::getMedianValue(m_windSpeed);
	}
}

float CV7::getTemperature()
{
	if (m_useMean) {
			return UtilityLibrary::getMeanValue(m_windTemperature);
	}
	else {
		return UtilityLibrary::getMedianValue(m_windTemperature);
	}
}



