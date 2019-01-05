cmake_minimum_required(VERSION 3.0.0)
project("snow-ray")
set(CMAKE_CXX_STANDARD 14)
# include dirs
include_directories(./src/ ./src/third-party/)
if (WIN32)
	include_directories(./ext/spdlog/include/)
endif(WIN32)

# === Core Module ===
set(CORE_SOURCES src/core/log.cpp
                 src/core/film.cpp)

# libs
if (WIN32)
else()
    set(BASIC_LIBS "-lm -lpthread -ldl")
endif(WIN32)

# tests
add_executable(test_vec test/test_vec.cpp ${CORE_SOURCES})
target_link_libraries(test_vec ${BASIC_LIBS})
