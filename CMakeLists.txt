cmake_minimum_required(VERSION 3.10)

project(cpp-aqi)

include(CTest)

set(CMAKE_CXX_STANDARD 14)

add_subdirectory(src)

if(BUILD_TESTING)
  add_subdirectory(tests)
endif()
