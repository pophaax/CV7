#define CATCH_CONFIG_MAIN
#include "../catch.hpp"
#include "CV7.h"


TEST_CASE("CV7Test")
{
	SECTION("Test CV7 refresh function")
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
		bool refresh_OK = true;
		while(polling--) {
			try {
				sensor.refreshData();
			} catch(const char* exception) {
				refresh_OK = false;
				cout << exception << endl;
			}
		}
		REQUIRE(refresh_OK);
	}
	SECTION("Test UtilLibrary parseString")
	{
		char testString[] = "$WIXDR,C,025.0,C,,*55$PLCJ,5DFF,5400,2E,4443,5041$PLCJE82B8,6BA0,2900,2162,80,$IIMWV,314.0,R,000.2,N,A*39$WIXDR,C,025.0,C,,*55$PLCJ,5DFE,54FF,2E,4443,5150$PLCJE82B8,6BA0,2900,2162,80,$IIMWV,314.0,R,000.2,N,A*39$WIXDR,C,025.0,C,,*55$PLCJ,5﻿";
		map<string,float> result = UtilityLibrary::parseString(testString);
		REQUIRE(result.find("windDirection")->second == 314);
		REQUIRE(result.find("windSpeed")->second == 0.2f);
		REQUIRE(result.find("windTemperature")->second == 25);
	}
	SECTION("Test UtilLibrary average")
	{
		bool average_OK = false;
		float f[] = {1.0,2.0,3.0};
		vector<float> v (f, f + sizeof(f) / sizeof(float) );
		float average = UtilityLibrary::getAverageValue(&v);
		REQUIRE(average == 2);
	}
	SECTION("Test UtilLibrary middle even")
	{
		bool middle_OK = false;
		float f[] = {1.0, 2.0, 20.0, 0.0, 5.0, 5.0};
		vector<float> v (f, f + sizeof(f) / sizeof(float) );
		float middle = UtilityLibrary::getMiddleValue(v);
		REQUIRE(middle == 3.5);
	}
	SECTION("Test UtilLibrary middle odd")
	{
		bool middle_OK = false;
		float f[] = {1.0, 2.0, 20.0, 5.0, 5.0};
		vector<float> v (f, f + sizeof(f) / sizeof(float) );
		float middle = UtilityLibrary::getMiddleValue(v);
		REQUIRE(middle == 5);
	}
	SECTION("Test UtilLibrary average one number")
	{
		bool average_OK = false;
		float f[] = {2.0};
		vector<float> v (f, f + sizeof(f) / sizeof(float) );
		float average = UtilityLibrary::getAverageValue(&v);
		REQUIRE(average == 2);
	}
	SECTION("Test UtilLibrary middle even")
	{
		bool middle_OK = false;
		float f[] = {5.0};
		vector<float> v (f, f + sizeof(f) / sizeof(float) );
		float middle = UtilityLibrary::getMiddleValue(v);
		REQUIRE(middle == 5);
	}
	SECTION("Test UtilLibrary average empty vector")
	{
		bool average_OK = false;
		float f[] = {};
		vector<float> v (f, f + sizeof(f) / sizeof(float) );
		float average = UtilityLibrary::getAverageValue(&v);
		REQUIRE(average == 0);
	}
	SECTION("Test UtilLibrary middle empty vector")
	{
		bool middle_OK = false;
		float f[] = {};
		vector<float> v (f, f + sizeof(f) / sizeof(float) );
		float middle = UtilityLibrary::getMiddleValue(v);
		REQUIRE(middle == 0);
	}
}
