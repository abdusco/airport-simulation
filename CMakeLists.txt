cmake_minimum_required(VERSION 3.8)
project(project2)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
        main.cpp
        models/Event.cpp models/Event.h
        models/EventType.cpp models/EventType.h
        models/Passenger.cpp models/Passenger.h
        Airport.cpp Airport.h
        models/Feature.h
        models/ControlPoint.cpp models/ControlPoint.h
        models/Report.cpp models/Report.h)

add_executable(project2 ${SOURCE_FILES})
