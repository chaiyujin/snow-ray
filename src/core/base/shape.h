#pragma once
#include "ray.h"
#include "intersect.h"

namespace snowrt {

class Shape : public IHitable {
public:
    Shape() {}
    Shape(const Shape& b) {}
    virtual ~Shape() {}
};

inline bool Quadratic(Float A, Float B, Float C, Float *t0, Float *t1) {
    Float disc = B*B - 4*A*C;
    if (disc < 0)  return false;
    Float sqrtDis = std::sqrt(disc);
    *t0 = 0.5*(-B - sqrtDis)/A;
    *t1 = 0.5*(-B + sqrtDis)/A;
#ifndef NDEBUG
    log::assertion(*t0<=*t1, "Quadratic t0>t1");
#endif
    return true;
}

}