cmake_minimum_required(VERSION 2.6)

project(ticktocktest)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

add_executable(ticktocktest
	tickTockTestMain.cpp
	
	PeriodicCounter.cpp
	Statistics.cpp
)

install(TARGETS ticktocktest RUNTIME DESTINATION bin)
