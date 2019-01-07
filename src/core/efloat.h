#pragma once
#include "base.h"
#include "log.h"

namespace snowrt {

class EFloat {
    /* members */
    Float mVal, mLower, mUpper;
#ifndef NDEBUG
    long double mPrecise;
#endif

public:
    static inline constexpr Float Gamma(int n) {
        return (n * constants::FloatEpsilon) / (1 - n * constants::FloatEpsilon);
    }
    void check() const {
        if (!std::isinf(mLower) && !std::isnan(mLower) &&
            !std::isinf(mUpper) && !std::isnan(mUpper))
            if (mLower > mUpper) log::fatal("{EFloat} lower > upper");
#ifndef NDEBUG
        if (!std::isinf(mVal) && !std::isnan(mVal)) {
            if (mLower > mPrecise) log::fatal("{EFloat} lower > precise");
            if (mUpper < mPrecise) log::fatal("{EFloat} upper < precise");
        }
#endif
    }

    EFloat() : mVal(0), mLower(0), mUpper(0) {
#ifndef NDEBUG
        mPrecise = mVal;
#endif
    }
    EFloat(const EFloat &b) : mVal(b.mVal), mLower(b.mLower), mUpper(b.mUpper) {
#ifndef NDEBUG
        mPrecise = mVal;
        check();
#endif
    }
    EFloat(Float val, Float error=0): mVal(val) {
        if (error == 0)
            mLower = mUpper = mVal;
        else {
            mLower = NextFloatDown(mVal - error);
            mUpper = NextFloatUp(mVal + error);
        }
#ifndef NDEBUG
        mPrecise = mVal;
        check();
#endif
    }

    EFloat &operator=(const EFloat &b) {
        b.check();
        if (&b != this) {
            mVal = b.mVal;
            mLower = b.mLower;
            mUpper = b.mUpper;
#ifndef NDEBUG
            mPrecise = b.mPrecise;
#endif
        }
    }

    EFloat operator+(const EFloat &f) const {
        EFloat r;
        r.mVal = mVal + f.mVal;
        r.mLower = NextFloatDown(lower() + f.lower());
        r.mUpper = NextFloatUp  (upper() + f.upper());
#ifndef NDEBUG
        r.mPrecise = mPrecise + f.mPrecise;
#endif  // DEBUG
        r.check();
        return r;
    }

    EFloat operator-(const EFloat &f) const {
        EFloat r;
        r.mVal = mVal - f.mVal;
        r.mLower = NextFloatDown(lower() - f.upper());
        r.mUpper = NextFloatUp  (upper() - f.lower());
#ifndef NDEBUG
        r.mPrecise = mPrecise - f.mPrecise;
#endif  // DEBUG
        r.check();
        return r;
    }

    EFloat operator*(const EFloat &f) const {
        EFloat r;
        r.mVal = mVal * f.mVal;
        const Float p0 = lower() * f.lower();
        const Float p1 = upper() * f.lower();
        const Float p2 = lower() * f.upper();
        const Float p3 = upper() * f.upper();
        r.mLower = NextFloatDown( std::min(std::min(p0, p1), std::min(p2, p3)) );
        r.mUpper = NextFloatUp  ( std::max(std::max(p0, p1), std::max(p2, p3)) );
#ifndef NDEBUG
        r.mPrecise = mPrecise * f.mPrecise;
#endif  // DEBUG
        r.check();
        return r;
    }

    EFloat operator/(const EFloat &f) const {
        EFloat r;
        r.mVal = mVal / f.mVal;
        const Float d0 = lower() / f.lower();
        const Float d1 = upper() / f.lower();
        const Float d2 = lower() / f.upper();
        const Float d3 = upper() / f.upper();
        r.mLower = NextFloatDown( std::min(std::min(d0, d1), std::min(d2, d3)) );
        r.mUpper = NextFloatUp  ( std::max(std::max(d0, d1), std::max(d2, d3)) );
#ifndef NDEBUG
        r.mPrecise = mPrecise / f.mPrecise;
#endif  // DEBUG
        r.check();
        return r;
    }

    EFloat operator-() const {
        EFloat r;
        r.mVal = -mVal;
        r.mLower = -mUpper;
        r.mUpper = -mLower;
#ifndef NDEBUG
        r.mPrecise = -mPrecise;
#endif
        r.check();
        return r;
    }

    bool operator==(Float f) const { return mVal == f; }
    bool operator==(const EFloat &ef) const { return mVal == ef.mVal; }
    friend EFloat sqrt(const EFloat &f);
    friend EFloat abs (const EFloat &f);

    explicit operator float()  const { return mVal; }
    explicit operator double() const { return mVal; }
    Float upper() const { return mUpper; }
    Float lower() const { return mLower; }
    Float error() const { return mUpper - mLower; }
#ifndef NDEBUG
    Float relativeError() const { return std::abs((mPrecise - mVal)/mPrecise); }
    long double precise() const { return mPrecise; }
#endif
};

inline EFloat operator+(Float a, const EFloat &b) { return EFloat(a) + b; }
inline EFloat operator-(Float a, const EFloat &b) { return EFloat(a) - b; }
inline EFloat operator+(const EFloat &a, Float b) { return a + EFloat(b); }
inline EFloat operator-(const EFloat &a, Float b) { return a - EFloat(b); }
inline EFloat operator*(Float a, const EFloat &b) { return EFloat(a) * b; }
inline EFloat operator/(Float a, const EFloat &b) { return EFloat(a) / b; }
inline EFloat operator*(const EFloat &a, Float b) { return a * EFloat(b); }
inline EFloat operator/(const EFloat &a, Float b) { return a / EFloat(b); }
inline EFloat sqrt(const EFloat &f) {
    EFloat r;
    r.mVal = std::sqrt(f.mVal);
    r.mLower = NextFloatDown(std::sqrt(f.lower()));
    r.mUpper = NextFloatUp  (std::sqrt(f.upper()));
#ifndef NDEBUG
    r.mPrecise = std::sqrt(f.mPrecise);
#endif
    r.check();
    return r;
}
inline EFloat abs(const EFloat &f) {
    if (f.lower() >= 0)
        // The entire interval is greater than zero, so we're all set.
        return f;
    else if (f.upper() <= 0) {
        // The entire interval is less than zero.
        EFloat r;
        r.mVal = -f.mVal;
        r.mLower = -f.mUpper;
        r.mUpper = -f.mLower;
#ifndef NDEBUG
        r.mPrecise = -f.mPrecise;
#endif
        r.check();
        return r;
    } else {
        // The interval straddles zero.
        EFloat r;
        r.mVal = std::abs(f.mVal);
        r.mLower = 0;
        r.mUpper = std::max(-f.mLower, f.mUpper);
#ifndef NDEBUG
        r.mPrecise = std::abs(f.mPrecise);
#endif
        r.check();
        return r;
    }
}

template <class ost> ost &operator<<(ost &out, const EFloat &ef) {
    out << (Float)ef << "[err:" << ef.error()
#ifndef NDEBUG
        << ",precise:" << ef.precise() << ",rel-err:" << ef.relativeError()
#endif
        << "]";
    return out;
}

inline bool Quadratic(EFloat A, EFloat B, EFloat C, EFloat *t0, EFloat *t1) {
    // Find quadratic discriminant
    double discrim = (double)B * (double)B - 4. * (double)A * (double)C;
    if (discrim < 0.) return false;
    double rootDiscrim = std::sqrt(discrim);

    EFloat floatRootDiscrim(rootDiscrim, constants::FloatEpsilon * rootDiscrim);

    // Compute quadratic _t_ values
    EFloat q;
    if ((Float)B < 0) q = -.5 * (B - floatRootDiscrim);
    else              q = -.5 * (B + floatRootDiscrim);
    *t0 = q / A;
    *t1 = C / q;
    if ((Float)*t0 > (Float)*t1) std::swap(*t0, *t1);
    return true;
}

}
