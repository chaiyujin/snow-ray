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
#define ALIGNED(bytes) __attribute__((aligned(bytes)))

}