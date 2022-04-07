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

#define RESOURCE_PATH "../resources/"

using namespace std;

typedef vector<vector<string>> table_type;

class WeatherStatistics {
public:
    explicit WeatherStatistics(vector<string> files = getFilePath(RESOURCE_PATH, filenames));
    time_t convertDateTime(string date, string time);
    bool isDateTimeValid(string date, string time);
    double getCoefficient(string start_date, string start_time, string end_date, string end_time);
    static vector<string> getFilePath(string prefix, vector<string> files);
private:
    map<time_t, double> timeToBarometricPressure;
    static vector<string> filenames;

    void loadData(vector<string> files);
};

#endif //CPP_CODE_CLINIC_WEATHERSTATISTICS_H
