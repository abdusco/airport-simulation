cmake_minimum_required(VERSION 3.8)
project(project2)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
        main.cpp
        Event.cpp Event.h
        EventType.cpp EventType.h
        Passenger.cpp Passenger.h
        Airport.cpp Airport.h
        Feature.h
        ControlPoint.cpp ControlPoint.h
        Report.cpp Report.h)

add_executable(project2 ${SOURCE_FILES})
