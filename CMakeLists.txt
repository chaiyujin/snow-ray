cmake_minimum_required(VERSION 3.0.0)
project("snow-ray")
set(CMAKE_CXX_STANDARD 14)
# include dirs
include_directories(./src/ ./src/third-party/)
if (WIN32)
	include_directories(./ext/spdlog/include/)
endif(WIN32)

# === Core Module ===
set(CORE_SOURCES src/core/utils/log.cpp
                 src/core/utils/random.cpp
                 src/core/utils/options.cpp
                 src/core/base/film.cpp)

# === Shapes Module ===
set(SHAPES_SOURCES src/shapes/sphere.cpp)

# libs
if (WIN32)
elseif(APPLE)
    set(BASIC_LIBS "-lm -lpthread -ldl")
else()
    set(BASIC_LIBS "-lm -lpthread -ldl -fopenmp")
endif()

# tests
set(CMAKE_CXX_FLAGS "-O3 -mavx")
add_executable(test_vec test/test_vec.cpp ${CORE_SOURCES})
add_executable(test_sphere test/test_sphere.cpp ${CORE_SOURCES} ${SHAPES_SOURCES})
add_executable(smallpt test/smallpt.cpp)
target_link_libraries(test_vec ${BASIC_LIBS})
target_link_libraries(test_sphere ${BASIC_LIBS})
