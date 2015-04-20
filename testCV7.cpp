#define CATCH_CONFIG_MAIN
#include "../catch.hpp"
#include "CV7.h"

using namespace std;
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
			} catch(const char* e) {
				string s = e;
				if (s.compare("CV7::refreshData: Serial read timeout") == 0 ) {
					refresh_OK = false;
				}
				else {
					// if no windsensor is connected "UtilLibrary::parseString exception" will always be thrown
				}
			}
		}
		REQUIRE(refresh_OK);
	}
	SECTION("Test UtilLibrary parseString SUCCESS")
	{
		char testString[] = "$WIXDR,C,025.0,C,,*55$PLCJ,5DFF,5400,2E,4443,5041$PLCJE82B8,6BA0,2900,2162,80,$IIMWV,314.0,R,000.2,N,A*39$WIXDR,C,025.0,C,,*55$PLCJ,5DFE,54FF,2E,4443,5150$PLCJE82B8,6BA0,2900,2162,80,$IIMWV,314.0,R,000.2,N,A*39$WIXDR,C,025.0,C,,*55$PLCJ,5﻿";
		bool hasException = false;
		try {
			map<std::string,float> result = UtilityLibrary::parseString(testString);
			REQUIRE(result.find("windDirection")->second == 314);
			REQUIRE(result.find("windSpeed")->second == 0.2f);
			REQUIRE(result.find("windTemperature")->second == 25);
		}
		catch (const char* exception) {
			hasException = true;
		}
		REQUIRE(hasException == false);
	}
	SECTION("Test UtilLibrary parseString FAIL")
	{
		char testString[] = "$WIXC,,*55$PLCJ,5DFF,5400,2E,4443,5041$P0,2162,80,$IIMWV,314.0,R,9$WIXC,,*55$PLCJ,5DFE,54FF,2E,4443,5150$PLCJE82B8,6BA0,2900,2162,80,$I,314.0,R,000.2,N,A*39$WIXC,025.0,C,,*55$PLCJ,5﻿";
		bool hasException = false;
		try {
			map<std::string,float> result = UtilityLibrary::parseString(testString);
		}
		catch (const char* exception) {
			hasException = true;
		}
		REQUIRE(hasException);
	}
	SECTION("Test UtilLibrary mean")
	{
		float f[] = {1.0,2.0,3.0};
		vector<float> v (f, f + sizeof(f) / sizeof(float) );
		float average = UtilityLibrary::getMeanValue(v);
		REQUIRE(average == 2);
	}
	SECTION("Test UtilLibrary median even")
	{
		float f[] = {1.0, 2.0, 20.0, 0.0, 5.0, 5.0};
		vector<float> v (f, f + sizeof(f) / sizeof(float) );
		float middle = UtilityLibrary::getMedianValue(v);
		REQUIRE(middle == 3.5);
	}
	SECTION("Test UtilLibrary median odd")
	{
		float f[] = {1.0, 2.0, 20.0, 5.0, 5.0};
		vector<float> v (f, f + sizeof(f) / sizeof(float) );
		float middle = UtilityLibrary::getMedianValue(v);
		REQUIRE(middle == 5);
	}
	SECTION("Test UtilLibrary mean one number")
	{
		float f[] = {2.0};
		vector<float> v (f, f + sizeof(f) / sizeof(float) );
		float average = UtilityLibrary::getMeanValue(v);
		REQUIRE(average == 2);
	}
	SECTION("Test UtilLibrary median even")
	{
		float f[] = {5.0};
		vector<float> v (f, f + sizeof(f) / sizeof(float) );
		float middle = UtilityLibrary::getMedianValue(v);
		REQUIRE(middle == 5);
	}
	SECTION("Test UtilLibrary mean empty vector")
	{
		vector<float> v;
		float average = UtilityLibrary::getMeanValue(v);
		REQUIRE(average == 0);
	}
	SECTION("Test UtilLibrary median empty vector")
	{
		vector<float> v;
		float middle = UtilityLibrary::getMedianValue(v);
		REQUIRE(middle == 0);
	}
	SECTION("Test UtilLibrary mean")
	{
		float f[] = {80, 280};
		vector<float> v (f, f + sizeof(f) / sizeof(float) );
		float average = UtilityLibrary::getMeanValue(v);
		REQUIRE(average == 0);
	}
	SECTION("Test UtilLibrary median even")
	{
		float f[] = {80, 280};
		vector<float> v (f, f + sizeof(f) / sizeof(float) );
		float middle = UtilityLibrary::getMedianValue(v);
		REQUIRE(middle == 0);
	}
	SECTION("Test UtilLibrary mean")
	{
		float f[] = {355, 357, 359, 1, 3};
		vector<float> v (f, f + sizeof(f) / sizeof(float) );
		float average = UtilityLibrary::getMeanValue(v);
		REQUIRE(average == 359);
	}
	SECTION("Test UtilLibrary median even")
	{
		float f[] = {355, 357, 359, 1, 3 };
		vector<float> v (f, f + sizeof(f) / sizeof(float) );
		float middle = UtilityLibrary::getMedianValue(v);
		REQUIRE(middle == 359);
	}
}
