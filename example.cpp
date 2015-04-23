#include <iostream>
#include <string>
#include <math.h>
#include <unistd.h>
#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/utility/setup/file.hpp>
#include "CV7.h"


using namespace std;
	/**
	 *  mode 0 = mean, 1 = median
	 */
vector<map<string, double>> getHZReadings(int mSeconds, bool mode) {
	string portName = "/dev/ttyAMA0";
	int baudRate = 4800;
	int bufferSize = 1;
	CV7 sensor;
	try {
		sensor.loadConfig(portName, baudRate);
	}
	catch (const char* exception) {
		cout << exception << endl;
	}

	sensor.setBufferSize(bufferSize); //Optional. Default: 30
	sensor.setUseMean(mode);
	vector<map<string, double>> array;
	int polling = 160;
	cout<<"loading values. 1 value/"<<mSeconds<<" ms"<<endl;
	int start = 0;
	float time = 0;
	map<string, double> temp;
	while (polling--) {
		start = clock();
		temp.clear();
		try {
			sensor.refreshData();
			temp.insert(make_pair("direction", sensor.getDirection()));
			temp.insert(make_pair("speed", sensor.getSpeed()));
			temp.insert(make_pair("temp", sensor.getTemperature()));
			array.push_back(temp);
			//cout<<".";
			//usleep(mSeconds);
		}
		catch (const char* exception) {
			cout << exception << endl;
		}
		time = ((clock()-start) / CLOCKS_PER_SEC)*1000;
		if (time < mSeconds ) {
			usleep(mSeconds - time);
		}

	}
	cout<<endl<<"loading done"<<endl;
	return array;
}
string prettyString (int number, float sin, float cos){
	string resultString = "no " + std::to_string(number);
	resultString += "  sin: " + std::to_string(sin);
	resultString += "  cos: " + std::to_string(cos);
	resultString += "\n";
	return resultString;
}

string sinAll(vector<map<string, double>> values){
	vector<float> fiveVector_s;
	vector<float> tenVector_s;
	vector<float> twentyVector_s;
	vector<float> fortyVector_s;
	vector<float> fiveVector_c;
	vector<float> tenVector_c;
	vector<float> twentyVector_c;
	vector<float> fortyVector_c;
	vector<float> resultFiveVector_s;
	vector<float> resultTenVector_s;
	vector<float> resultTwentyVector_s;
	vector<float> resultFortyVector_s;
	vector<float> resultFiveVector_c;
	vector<float> resultTenVector_c;
	vector<float> resultTwentyVector_c;
	vector<float> resultFortyVector_c;
	vector<string> resultStringVector;
	for (map<string, double> &m : values) {
		double tempSin = sin(m.find("direction")->second * (M_PI / 180));
		double tempCos = cos(m.find("direction")->second * (M_PI / 180));
		resultStringVector.push_back(
				"map: [ dir: " + to_string(m.find("direction")->second) + " sin dir: "
				+ to_string(tempSin)	+ " cos dir: "	+ to_string(tempCos) + "]"
		);
		if (fiveVector_s.size() > 5)		{
			resultFiveVector_s.push_back(UtilityLibrary::getMeanValue(fiveVector_s));
			resultFiveVector_c.push_back(UtilityLibrary::getMeanValue(fiveVector_c));
			fiveVector_s.clear();
			fiveVector_c.clear();
		}
		if (tenVector_s.size() > 10) 		{
			resultTenVector_s.push_back(UtilityLibrary::getMeanValue(tenVector_s));
			resultTenVector_c.push_back(UtilityLibrary::getMeanValue(tenVector_c));
			tenVector_s.clear();
			tenVector_c.clear();
		}
		if (twentyVector_s.size() > 20) 	{
			resultTwentyVector_s.push_back(UtilityLibrary::getMeanValue(twentyVector_s));
			resultTwentyVector_c.push_back(	UtilityLibrary::getMeanValue(twentyVector_c));
			twentyVector_s.clear();
			twentyVector_c.clear();
		}
		if (fortyVector_s.size() > 40) 	{
			resultFortyVector_s.push_back(UtilityLibrary::getMeanValue(fortyVector_s));
			resultFortyVector_c.push_back(UtilityLibrary::getMeanValue(fortyVector_c));
			fortyVector_s.clear();
			fortyVector_c.clear();
		}
		fiveVector_s.push_back(tempSin);
		tenVector_s.push_back(tempSin);
		twentyVector_s.push_back(tempSin);
		fortyVector_s.push_back(tempSin);
		fiveVector_c.push_back(tempCos);
		tenVector_c.push_back(tempCos);
		twentyVector_c.push_back(tempCos);
		fortyVector_c.push_back(tempCos);

	}
	string resultString = "resultstring:\n";
	BOOST_LOG_TRIVIAL(info) <<endl<<"resultstring:";
	for (string s : resultStringVector) {
		resultString += s + "\n";
		BOOST_LOG_TRIVIAL(info) << s;
	}
	resultString += "fiveVector:\n";
	BOOST_LOG_TRIVIAL(info) <<"fiveVector:";
	int i = 0;
	for (float f : resultFiveVector_s) {
		resultString += prettyString(i, f, resultFiveVector_c.at(i));
		BOOST_LOG_TRIVIAL(info)<< "no " << i<<"  sin: " << f <<"  cos: " << resultFiveVector_c.at(i);
		i++;
	}
	resultString += "tenVector:\n";
	BOOST_LOG_TRIVIAL(info) <<"tenVector:";
	i = 0;
	for (float f : resultTenVector_s) {
		resultString += prettyString(i, f, resultTenVector_c.at(i));
		BOOST_LOG_TRIVIAL(info)<< "no " << i<<"  sin: " << f <<"  cos: " << resultTenVector_c.at(i);
		i++;
	}
	resultString += "twentyVector:\n";
	BOOST_LOG_TRIVIAL(info) <<"twentyVector:" ;
	i = 0;
	for (float f : resultTwentyVector_s) {
		resultString += prettyString(i, f, resultTwentyVector_c.at(i));
		BOOST_LOG_TRIVIAL(info)<< "no " << i<<"  sin: " << f <<"  cos: " << resultTwentyVector_c.at(i);
		i++;
	}
	resultString += "fortyVector:\n";
	BOOST_LOG_TRIVIAL(info) <<"fortyVector:";
	i = 0;
	for (float f : resultFortyVector_s) {
		resultString += prettyString(i, f, resultFortyVector_c.at(i));
		BOOST_LOG_TRIVIAL(info)<< "no " << i<<"  sin: " << f <<"  cos: " << resultFortyVector_c.at(i);
		i++;
	}
	return resultString;
}
void runOldExample(){
	string portName = "/dev/ttyAMA0";
	int baudRate = 4800;
	unsigned int bufferSize = 10;
	bool inputOk = false;
	int i;
	while (inputOk == false) {
		cout << "Please enter a baudrate (rec: 4800):" << endl;
		cin >> i;
		if (i <= 5000 && i >= 3000) {
			cout << "Baudrate set to: " << i << endl;
			baudRate = i;
			inputOk = true;
		} else {
			cout << "Input not in acceptable range, try something else: "
					<< endl;
		}
	}
	inputOk = false;
	while (inputOk == false) {
		cout << "Please enter a buffersize (rec: 10):" << endl;
		cin >> i;

		if (i <= 50 && i >= 1) {
			cout << "Buffersize set to " << i << endl;
			bufferSize = i;
			inputOk = true;
		} else {
			cout << "Input not in acceptable range, try something else: "
					<< endl;
		}

	}
	BOOST_LOG_TRIVIAL(info)<< "Running CV7 example:";
	cout << "Running CV7 example: " << endl;

	CV7 sensor;

	try {
		sensor.loadConfig(portName, baudRate);
	} catch (const char* exception) {
		BOOST_LOG_TRIVIAL(error)<< "crash at sensor.loadConfif : "<< exception;
		cout << exception << endl;
	}
	sensor.setBufferSize(bufferSize); //Optional. Default: 30

	int polling = 50;
	float wd_a, ws_a, wt_a, wd_b, ws_b, wt_b;
	BOOST_LOG_TRIVIAL(info)<< "Entering test loop, looping "<< polling<< "times" ;
	while (polling--) {
		try {
			sensor.refreshData();
		} catch (const char* exception) {
			BOOST_LOG_TRIVIAL(error)<< "crash at refreshData : "<< exception;
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

		cout << "Mean Angle	: " << wd_a << " Speed: " << ws_a << " Temp: "
				<< wt_a << endl << "Median Angle	: " << wd_b << " Speed: "
				<< ws_b << " Temp: " << wt_b << endl;
		BOOST_LOG_TRIVIAL(info)<< "Mean Angle	: " << wd_a << " Speed: " << ws_a << " Temp: "
				<< wt_a << endl << "Median Angle	: " << wd_b << " Speed: "
				<< ws_b << " Temp: " << wt_b;
	}

}


int main(int argc, char** argv)
{
	boost::log::add_file_log("sample.log");
	boost::log::core::get()->set_filter(
			boost::log::trivial::severity >= boost::log::trivial::info
	);

	/**
	 *  CV7 integration test
	 */
	int times = 1; // 100 for standard reading
	BOOST_LOG_TRIVIAL(info)<< "reading info from windsensor with "<< 2000*times <<" freq";
	vector<map<string, double>> values = getHZReadings(2000*times, false);
	string log = sinAll(values);
	BOOST_LOG_TRIVIAL(info)<< "reading info from windsensor with "<< 1000*times <<" freq";
	values = getHZReadings(1000 * times, false);
	log = sinAll(values);
	BOOST_LOG_TRIVIAL(info)<< "reading info from windsensor with "<< 500*times <<" freq";
	values = getHZReadings(500 * times, false);
	log = sinAll(values);
	BOOST_LOG_TRIVIAL(info)<< "reading info from windsensor with "<< 250*times <<" freq";
	values = getHZReadings(250 * times, false);
	log = sinAll(values);

	runOldExample();
	
}



