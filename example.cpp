#include <iostream>
#include "CV7.h"

using namespace std;
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
	float wd_a, ws_a, wt_a, wd_b, ws_b, wt_b;
	while(polling--) {
		try {
			sensor.refreshData();
		} catch(const char* exception) {
			cout << exception << endl;
		}
		sensor.setUseMean(true);
		wd_a = sensor.getDirection();
		ws_a = sensor.getSpeed();
		wt_a = sensor.getTemperature();
		sensor.setUseMean(false);
		wd_b = sensor.getDirection();
		ws_b = sensor.getSpeed();
		wt_b = sensor.getTemperature();
		
		cout 	<< "Mean Angle	: " << wd_a << " Speed: " << ws_a << " Temp: " << wt_a << endl
				<< "Median Angle	: " << wd_b << " Speed: " << ws_b << " Temp: " << wt_b << endl;
	}

	return 0;

}
