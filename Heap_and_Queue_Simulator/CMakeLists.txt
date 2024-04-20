cmake_minimum_required(VERSION 3.0.0)
project("CS2040C AY23/24 SEM2 ASSIGNMENT 4")

# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
  # SOURCE_DIR googletest-03597a01ee50ed33e9dfd640b249b4be3799d395
  # FETCHCONTENT_FULLY_DISCONNECTED
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_library(queue_sim customer.cpp queue_simulator.cpp)

enable_testing()


add_executable(queue_sim_test queue_simulator_test.cpp)
target_link_libraries(queue_sim_test queue_sim GTest::gtest_main)

add_test(NAME QueueSimTest COMMAND queue_sim_test)
