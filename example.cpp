#include <iostream>
#include "CV7.h"


int main()
{
	string portName = "/dev/ttyAMA0";
	int baudRate = 4800;
	unsigned int bufferSize = 10; 

	CV7 sensor;

	try {
		sensor.loadConfig(portName, baudRate);
	} catch(const char* exception) {
		cout << exception << endl;
	}

	sensor.setBufferSize(bufferSize); //Optional. Default: 30

	int polling = 50;
	float wd, ws, wt;
	while(polling--) {

		try {
			sensor.refreshData();
		} catch(const char* exception) {
			cout << exception << endl;
		}

		wd = sensor.getWindDirection();
		ws = sensor.getWindSpeed();
		wt = sensor.getWindTemperature();
		
		cout << "Angle: " << wd << " Speed: " << ws << " Temp: " << wt << endl;
	}

	return 0;

}
