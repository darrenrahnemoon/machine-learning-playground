cmake_minimum_required(VERSION 3.22)

project(MachineLearning)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(Main src/Main.cpp)
target_include_directories(Main 
	PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include"
	PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src"
)