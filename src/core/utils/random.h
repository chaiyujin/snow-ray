#pragma once
#include "vec.h"
#include <random>

namespace snowrt {
namespace random {

Float uniform();
inline Float3 InUnitSphere() {
    Float r1 = uniform() * constants::Pi * 2;
    Float r2 = uniform() * constants::Pi;
    Float3 w(0, 0, 1);
    Float3 u(0, 1, 0);
    Float3 v(1, 0, 0);
    Float  a = std::sin(r2);
    return Float3(
        std::cos(r1) * a,
        std::sin(r1) * a,
        std::cos(r2)
    );
}

inline Float3 InHemiShpere(const Float3 &normal) {
    Float r1 = uniform() * constants::Pi * 2;
    Float r2 = uniform();
    Float r2s = std::sqrt(r2);
    Float3 w = normal.normalized();
    Float3 u = Cross((std::abs(w.x)>.1)? Float3(0, 1, 0) : Float3(1, 0, 0),
                     w).normalized();
    Float3 v = Cross(w, u);
    return (u * (std::cos(r1) * r2s) + 
            v * (std::sin(r1) * r2s) +
            w * std::sqrt(1-r2));
}


}}