/*
 * MockWindsensor.h
 *
 *  Created on: Apr 23, 2015
 *      Author: sailbot
 */

#ifndef CV7_MOCKWINDSENSOR_H_
#define CV7_MOCKWINDSENSOR_H_

#include "CV7.h"

class MockWindsensor:public CV7 {
	public:

		void loadConfig(std::string portName, int baudRate);

		void setBufferSize(unsigned int bufferSize);

		void setBaudRate(unsigned int baudRate);

		void setPortName(std::string portName);

		unsigned int getBufferSize();

		std::string refreshData();

		float getDirection();

		float getSpeed();

		float getTemperature();

		bool isUseMean();
		void setUseMean(bool useMean);
};
#endif /* CV7_MOCKWINDSENSOR_H_ */
