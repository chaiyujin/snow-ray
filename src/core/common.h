#pragma once
#include <cmath>
#include <limits>
#include <stdint.h>
#include <string.h>
#include <iostream>

// #define USING_DOUBLE_PRECISION

// define Float
#ifdef USING_DOUBLE_PRECISION
typedef double Float;
#else
typedef float  Float;
#endif

// aligned for struct
#ifdef WIN32
#define ALIGNED(bytes) __declspec(align(bytes))
#else
#define ALIGNED(bytes) __attribute__((aligned(bytes)))
#endif

/* utils */
namespace snowrt {
namespace constants {
    constexpr const Float Infinity = std::numeric_limits<Float>::infinity();
    constexpr const Float MaxFloat = std::numeric_limits<Float>::max();
    constexpr const Float FloatEpsilon = std::numeric_limits<Float>::epsilon() * 0.5;
    constexpr const Float Pi = (Float)3.14159265358979323846;
}
template <class T, class U> inline U Lerp(T t, U a, U b)  { return a * (1-t) + b * t; }
template <class T, class U> inline T Clamp(T x, U a, U b) { return (x < a)? (T)a : ((x > b)? (T)b : x); }
}

namespace snowrt {

/* class collection */

class Ray;
class Shape;
class Interaction;

/* interface */

class IHitable;

}