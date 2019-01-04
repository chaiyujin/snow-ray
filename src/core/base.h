#pragma once
#include <cmath>
#include <limits>
#include <stdint.h>

/* definitions */
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

namespace constants {
    constexpr const Float Infinity = std::numeric_limits<Float>::infinity();
    constexpr const Float MaxFloat = std::numeric_limits<Float>::max();
    constexpr const Float Pi = (Float)3.14159265358979323846;
}
}

/* common utils */
namespace snowray {
template <class T, class U>
inline U Lerp(T t, U a, U b) {
    return a * (1-t) + b * t;
}
}