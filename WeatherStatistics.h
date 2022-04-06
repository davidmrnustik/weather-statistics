//
// Created by David Mrnustik on 6/4/22.
//

#ifndef CPP_CODE_CLINIC_WEATHERSTATISTICS_H
#define CPP_CODE_CLINIC_WEATHERSTATISTICS_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <ctime>
#include <sstream>
#include <map>

#define RESOURCE_PATH "resources/"

using namespace std;

typedef vector<vector<string>> table_type;

class WeatherStatistics {
public:
    WeatherStatistics();
    time_t convertDateTime(string date, string time);
    bool isDateTimeValid(string date, string time);
    double getCoefficient(string start_date, string start_time, string end_date, string end_time);
private:
    table_type weatherData;
    map<time_t, double> timeToBarometricPressure;

    vector<string> parseRow(const string& s);
    void readFile(string filename, table_type *data);
    void loadData();
};

#endif //CPP_CODE_CLINIC_WEATHERSTATISTICS_H
