# Weather Statistics
Weather Statistics is a command line app written in c++ (v14).
Application returns a weather condition (sunny/stormy) based on barometric pressure within an entered time range.

This project was part of LinkedIn Course [Code Clinic: C++](https://www.linkedin.com/learning/code-clinic-c-plus-plus-2).
A code is a mixture of own and teachers' code solution. 

## Build
It's a cmake (v3.21) project. Run following commands to build it:
```
mkdir build
cd build
cmake ../
make
```

### Resources
A part of project are .txt files (not stored in this repository) that should be stored in your build folder under `./resources` folder with name syntax `Environmental_Data_Deep_Moor_YYYY.txt` where `YYYY` is a full year format `2022` and content structure:

```
date       time    	Air_Temp	Barometric_Press	Dew_Point	Relative_Humidity	Wind_Dir	Wind_Gust	Wind_Speed
2012_01_01 00:02:14	34.30	30.50	26.90	74.20	346.40	11.00	 3.60
```

To check structure, there is also a mock weather statistics file (for test purposes) in `/tests/WeatherStatisticsMockData.txt`

### Run
```
cd build
./weather_statistics
```