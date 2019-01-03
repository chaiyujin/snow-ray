#pragma once
#include <cmath>
#include <stdint.h>

namespace snowray {

// define Float
#ifdef USING_DOUBLE_PRECISION
typedef double Float;
#else
typedef float Float;
#endif

// aligned
#ifdef WIN32
#define ALIGNED(bytes) __declspec(align(bytes))
#else
#define ALIGNED(bytes) __attribute__((aligned(bytes)))
#endif
}