cmake_minimum_required(VERSION 3.24)
project(Dictionary)

set(CMAKE_CXX_STANDARD 17)

add_executable(Dictionary main.cpp Dictionary.h Couple.h ClosedHash.h Hash.h OpenHash.h)
