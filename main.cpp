//
// Created by David Mrnustik on 6/4/22.
//
#include "WeatherStatistics.h"

int main() {
    WeatherStatistics weatherStats;
    string start_date, start_time, end_date, end_time;

    cout << "Enter START DATE as yyyy_mm_dd: ";
    cin >> start_date;

    cout << "Enter START TIME as hh:mm:ss (24-hour): ";
    cin >> start_time;

    if (!weatherStats.isDateTimeValid(start_date, start_time))
    {
        return 1;
    }

    cout << "Enter END DATE as yyyy_mm_dd: ";
    cin >> end_date;

    cout << "Enter END TIME as hh:mm:ss (24-hour): ";
    cin >> end_time;

    if (!weatherStats.isDateTimeValid(end_date, end_time))
    {
        return 1;
    }

    double coefficient = weatherStats.getCoefficient(start_date, start_time, end_date, end_time);

    if (coefficient < 0)
    {
        cout << "Stormy conditions." << endl;
    }
    else
    {
        cout << "Sunny conditions." << endl;
    }

    return 0;
}