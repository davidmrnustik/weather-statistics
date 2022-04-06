#include "WeatherStatistics.h"

WeatherStatistics::WeatherStatistics()
{
    loadData();
}

void WeatherStatistics::loadData()
{
    vector<string> filenames = {
        "Environmental_Data_Deep_Moor_2012.txt",
        "Environmental_Data_Deep_Moor_2013.txt",
        "Environmental_Data_Deep_Moor_2014.txt",
        "Environmental_Data_Deep_Moor_2015.txt"
    };

    for(string& filename: filenames) {
        ifstream ifs;
        ostringstream pathStream;
        pathStream << RESOURCE_PATH << filename;

        string path = pathStream.str();

        ifs.open(path);
        cout << "Loading " << path << endl;

        if (!ifs)
            throw runtime_error("couldn't open a file");

        string line;
        int i = 0;

        while(getline(ifs, line))
        {
            i++;
            if (i <= 1) continue;

            istringstream buffer(line);
            string time, date;
            double air_temp, barometric_press, dew_point, relative_humidity, wind_dir, wind_gust, wind_speed;

            buffer >> date >> time >> air_temp >> barometric_press >> dew_point >> relative_humidity >> wind_dir >> wind_gust >> wind_speed;

            time_t dateTime = convertDateTime(date, time);
            timeToBarometricPressure[dateTime] = barometric_press;

            // auto fields = parseRow(line);
            // weatherData.push_back(fields);
        }

        ifs.close();
    }
}

time_t WeatherStatistics::convertDateTime(string date, string time)
{
    string datetime;
    int year, month, day;

    if (sscanf(date.c_str(), "%d_%d_%d", &year, &month, &day) != 3)
    {
        cerr << "Failed parsed date " << date << endl;
        return -1;
    }

    int hour, minute, sec = 0;

    if (sscanf(time.c_str(), "%d:%d:%d", &hour, &minute, &sec) != 3)
    {
        cerr << "Failed parsed time " << time << endl;
        return -2;
    }

    struct tm dateTime = {};

    dateTime.tm_year = year - 1900; // years since 1900
    dateTime.tm_mon = month;
    dateTime.tm_mday = day;
    dateTime.tm_hour = hour;
    dateTime.tm_min = minute;
    dateTime.tm_sec = sec;

    return mktime(&dateTime);
}

bool WeatherStatistics::isDateTimeValid(string date, string time)
{
    time_t dateTime = convertDateTime(date, time);

    if (dateTime < 0) {
        return false;
    }

    return true;
}

double WeatherStatistics::getCoefficient(string start_date, string start_time, string end_date, string end_time)
{
    time_t startDateTime = convertDateTime(start_date, start_time);
    time_t endDateTime = convertDateTime(end_date, end_time);

    if (endDateTime < startDateTime)
    {
        exit(1);
    }

    map<time_t, double>::iterator startDateTimeBarometricPressure;
    map<time_t, double>::iterator endDateTimeBarometricPressure;

    startDateTimeBarometricPressure = timeToBarometricPressure.lower_bound(startDateTime);
    endDateTimeBarometricPressure = timeToBarometricPressure.lower_bound(endDateTime);

    double timeDiff = endDateTimeBarometricPressure->first - startDateTimeBarometricPressure->first;
    double barometricPressureDiff = endDateTimeBarometricPressure->second - startDateTimeBarometricPressure->second;

    return barometricPressureDiff / timeDiff;
}

// Previous solution for parsing a row
// Example of row: 2012_01_01 00:02:14	34.30	30.50	26.90	74.20	346.40	11.00	 3.60
vector<string> WeatherStatistics::parseRow(const string& s)
{
    vector<string> fields {""};

    size_t i = 0;

    for(char c: s)
    {
        switch (c)
        {
            case '\r':
                i++;
                break;
            case '\t':
                fields.emplace_back("");
                i++;
                break;
            case ' ':
                if (i == 0) {
                    fields.emplace_back("");
                    i++;
                    break;
                }
            default:
                fields[i].push_back(c);
        }
    }
    return fields;
}

// Previous solution for reading a row/line
void WeatherStatistics::readFile(string filename, table_type *data)
{
    ifstream ifs;
    filename = "resources/" + filename;

    ifs.open(filename);
    cout << "Loading " << filename << endl;

    if (!ifs)
        throw runtime_error("couldn't open a file");

    string s;
    int i = 0;

    while(getline(ifs, s))
    {
        i++;
        if (i <= 1) continue;
        auto fields = parseRow(s);
        data->push_back(fields);
    }

    ifs.close();
}