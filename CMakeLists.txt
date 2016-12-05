cmake_minimum_required(VERSION 3.6)
project(AsymCryptoLaba2_RSA)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")#-lgmpxx

set(SOURCE_FILES main.cpp utils.h)
add_executable(AsymCryptoLaba2_RSA ${SOURCE_FILES})