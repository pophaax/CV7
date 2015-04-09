#ifndef __CV7_H__
#define __CV7_H__

#include <string>
#include <vector>
#include <map>
#include "UtilityLibrary.h"

using namespace std;

class CV7 {
	
	public:

		CV7();
		~CV7();

		/*
			Loads the CV7 windsensor.
		*/
		void loadConfig(string portName, int baudRate);

		/*
			Sets vector sizes. Must be greater than 0 and default value is 30.
		*/
		void setBufferSize(unsigned int bufferSize);
		
		/*
			Returns current bufferSize value set.
		*/
		unsigned int getBufferSize();
		
		/*
			Gets a new reading from the sensor and adds them to the buffer vectors.
		*/
		void refreshData();
		
		/*
			Returns an average wind direction value, depending on how many values that is in vector.
		*/
		float getDirection();
		
		/*
			Returns an average wind speed value, depending on how many values that is in vector.
		*/
		float getSpeed();
		
		/*
			Returns an average wind temperature value, depending on how many values that is in vector.
		*/
		float getTemperature();

		bool isUseMean();
		void setUseMean(bool useMean);

	private:
		bool m_useMean;
		int m_fd;

		unsigned int m_bufferSize;
		
		vector<float> m_windDirection;
		vector<float> m_windSpeed;
		vector<float> m_windTemperature;
};

#endif
