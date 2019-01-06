#pragma once
#include "base.h"

namespace snowrt {

class EFloat {
    static inline constexpr Float gamma(int n) {
        return (n * constants::FloatEpsilon) / (1 - n * constants::FloatEpsilon);
    }
    /* members */
    Float v, err;
#ifndef NDEBUG
    long double ld;
#endif

public:
    EFloat() : v(0), err(0) {
#ifndef NDEBUG
        ld = v;
#endif
    }
    EFloat(Float val, Float error=0): v(val), err(error) {
#ifndef NDEBUG
        ld = v;
#endif
    }

    EFloat operator+(EFloat f) const {
        EFloat r;
        r.v = v + f.v;
        r.err = err + f.err +
            gamma(1) * (std::abs(v + f.v) + err + f.err);
#ifndef NDEBUG
        r.ld = ld + f.ld;
#endif  // DEBUG
        return r;
    }
    explicit operator float()  const { return v; }
    explicit operator double() const { return v; }

    Float upper() const { return NextFloatUp(v + err); }
    Float lower() const { return NextFloatDown(v - err); }
    Float error() const { return err; }
#ifndef NDEBUG
    Float relativeError() const { return std::abs((ld - v)/ld); }
    long double preciseValue() const { return ld; }
#endif
};

}