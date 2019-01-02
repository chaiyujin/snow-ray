cmake_minimum_required(VERSION 3.0.0)
project("snow-ray")
set(CMAKE_CXX_STANDARD 14)
include_directories("src")

if (WIN32)
else()
    set(BASIC_LIBS "-lm -lpthread -ldl")
endif(WIN23)

# tests
add_executable(test_vec test/test_vec.cpp)
target_link_libraries(test_vec ${BASIC_LIBS})