cmake_minimum_required(VERSION 3.12)

project(LinkedListProject)

add_executable(linkedlist main.cpp)

# Set C++ standard (optional, based on your requirement)
if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET linkedlist PROPERTY CXX_STANDARD 20)
endif()