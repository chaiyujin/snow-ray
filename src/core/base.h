#pragma once
#include <cmath>
#include <limits>
#include <stdint.h>
#include <string.h>
#include <iostream>

/* definitions */
namespace snowrt {
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
namespace snowrt {
template <class T, class U>
inline U Lerp(T t, U a, U b) {
    return a * (1-t) + b * t;
}
template <class T, class U>
inline T Clamp(T x, U a, U b) {
    if (x < a)      return (T)a;
    else if (x > b) return (T)b;
    else return x;
}
}

/* class collection */
namespace snowrt {

class Ray;
class Shape;
class Interaction;

}