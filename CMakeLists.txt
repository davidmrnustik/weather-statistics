cmake_minimum_required(VERSION 3.21)
project(weather_statistics)

set(CMAKE_CXX_STANDARD 14)

add_executable(weather_statistics WeatherStatistics.cpp main.cpp WeatherStatistics.h)
