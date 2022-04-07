cmake_minimum_required(VERSION 3.21)

set(TARGET weather_statistics)

project(${TARGET})
include(FetchContent)

enable_testing()

set(CMAKE_CXX_STANDARD 14)

FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG        703bd9caab50b139428cea1aaff9974ebee5742e
)
FetchContent_MakeAvailable(googletest)

target_compile_definitions(gtest
    PUBLIC
    GTEST_LANG_CXX20
    GTEST_HAS_TR1_TUPLE=0
)

add_executable(tests tests/WeatherStatistics.test.cpp WeatherStatistics.cpp WeatherStatistics.h)

add_executable(${TARGET} main.cpp WeatherStatistics.cpp WeatherStatistics.h)

set_target_properties(tests PROPERTIES COMPILE_FLAGS "${cxx_strict}")

target_link_libraries(tests gtest gtest_main)