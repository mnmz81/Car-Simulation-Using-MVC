cmake_minimum_required(VERSION 3.5)
project(3)

set(CMAKE_CXX_STANDARD 11)

add_executable(3 Point.cpp Point.h Vehicles.cpp Vehicles.h TrooperState.cpp TrooperState.h Chopper.cpp Chopper.h main.cpp MapObject.cpp MapObject.h Warehouse.cpp Warehouse.h Delivery.cpp Delivery.h FileHandlerWarhouse.cpp FileHandlerWarhouse.h Controller.cpp Controller.h)