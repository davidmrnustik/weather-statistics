//
// Created by David Mrnustik on 7/4/22.
//

#include "../WeatherStatistics.h"
#include "gtest/gtest.h"

const vector<string> mockFile = {"../tests/WeatherStatisticsMockData.txt"};

TEST(WeatherStatistics, NonValidFile) {
    EXPECT_ANY_THROW(WeatherStatistics w {{"nothing.txt"}});
}

TEST(WeatherStatistics, ValidFilePath) {
    WeatherStatistics w {mockFile};
    vector<string> expected = mockFile;
    EXPECT_EQ(w.getFilePath("../tests/", {"WeatherStatisticsMockData.txt"}), expected);
}

TEST(WeatherStatistics, StartDateAndTimeAreValid) {
    WeatherStatistics w {mockFile};
    string date = "2015_01_01";
    string time = "11:00:00";

    EXPECT_TRUE(w.isDateTimeValid(date, time));
}

TEST(WeatherStatistics, DateIsNotValid) {
    WeatherStatistics w {mockFile};
    string date = "2015_0101";
    string time = "11:00:00";

    EXPECT_FALSE(w.isDateTimeValid(date, time));
}

TEST(WeatherStatistics, TimeIsNotValid) {
    WeatherStatistics w {mockFile};
    string date = "2015_01_01";
    string time = "11:0000";

    EXPECT_FALSE(w.isDateTimeValid(date, time));
}

TEST(WeatherStatistics, ValidConvertDateTime) {
    WeatherStatistics w {mockFile};
    string date = "2015_01_01";
    string time = "11:00:00";

    struct tm tm_time {00, 00, 11, 01, 01, 2015 - 1900};

    time_t expected = mktime(&tm_time);

    ASSERT_EQ(w.convertDateTime(date, time), expected);
}

TEST(WeatherStatistics, NonValidConvertDate) {
    WeatherStatistics w {mockFile};
    string date = "2015_0101";
    string time = "11:00:00";

    ASSERT_EQ(w.convertDateTime(date, time), -1);
}

TEST(WeatherStatistics, NonValidConvertTime) {
    WeatherStatistics w {mockFile};
    string date = "2015_01_01";
    string time = "11:0000";

    ASSERT_EQ(w.convertDateTime(date, time), -2);
}
TEST(WeatherStatistics, NonValidEndDate) {
    WeatherStatistics w {mockFile};

    string startDate = "2015_01_01";
    string startTime = "11:00:00";

    string endDate = "2014_01_01";
    string endTime = "11:00:00";

    EXPECT_EXIT(w.getCoefficient(startDate, startTime, endDate, endTime), testing::ExitedWithCode(1), ".*");

}

TEST(WeatherStatistics, ValidSunnyCoefficient) {
    WeatherStatistics w {mockFile};

    string startDate = "2012_01_01";
    string startTime = "00:02:00";

    string endDate = "2012_01_01";
    string endTime = "01:40:00";

    ASSERT_GT(w.getCoefficient(startDate, startTime, endDate, endTime), 0);
}

TEST(WeatherStatistics, ValidStormyCoefficient) {
    WeatherStatistics w {mockFile};

    string startDate = "2012_01_01";
    string startTime = "00:02:00";

    string endDate = "2012_01_01";
    string endTime = "01:50:00";

    ASSERT_LT(w.getCoefficient(startDate, startTime, endDate, endTime), 0);
}