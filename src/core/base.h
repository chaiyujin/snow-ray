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
typedef double   Float;
typedef uint64_t UInteger;
typedef int64_t  Integer;
#define NEG_ZERO -0.0
#define POS_ZERO 0.0
#else
typedef float    Float;
typedef uint32_t UInteger;
typedef int32_t  Integer;
#define NEG_ZERO -0.f
#define POS_ZERO 0.f
#endif

inline UInteger FloatToBits(Float v) {
    UInteger ret;
    memcpy(&ret, &v, sizeof(UInteger));
    return ret;
}

inline Float BitsToFloat(UInteger v) {
    Float ret;
    memcpy(&ret, &v, sizeof(Float));
    return ret;
}

inline Float NextFloatUp(Float v) {
    if (std::isinf(v) && v > POS_ZERO) return v;
    if (v == NEG_ZERO) v = POS_ZERO;  // -0 -> 0
    UInteger ui = FloatToBits(v);
    if (v >= POS_ZERO) ++ui; else --ui;
    return BitsToFloat(ui);
}

inline Float NextFloatDown(Float v) {
    if (std::isinf(v) && v < NEG_ZERO) return v;
    if (v == POS_ZERO) v = NEG_ZERO;  // 0 -> -0
    UInteger ui = FloatToBits(v);
    if (v <= NEG_ZERO) ++ui; else --ui;
    return BitsToFloat(ui);
}


// aligned
#ifdef WIN32
#define ALIGNED(bytes) __declspec(align(bytes))
#else
#define ALIGNED(bytes) __attribute__((aligned(bytes)))
#endif

namespace constants {
    constexpr const Float Infinity = std::numeric_limits<Float>::infinity();
    constexpr const Float MaxFloat = std::numeric_limits<Float>::max();
    constexpr const Float FloatEpsilon = std::numeric_limits<Float>::epsilon() * 0.5;
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