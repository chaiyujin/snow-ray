#pragma once
#include <stdint.h>
#include <stdlib.h>

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

