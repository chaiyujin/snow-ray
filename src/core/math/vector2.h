#pragma once
#include "base.h"

namespace snowray::math {

/**
 * Vector2
 * */
template <class Scalar>
struct ALIGNED(16) Vector2 {
    union {
        Scalar data[2];
        struct { Scalar x, y; };
    };

    inline Vector2();
    inline Vector2(const Vector2 &b);
    inline explicit Vector2(Scalar a);
    inline explicit Vector2(Scalar a, Scalar b);
    inline explicit Vector2(const Scalar *ptr);
    // check finite
    inline bool isnan() const;
    inline bool isinf() const;
    inline bool isfinite() const;
    // indexing
    inline       Scalar&  at(uint32_t index);
    inline const Scalar&  at(uint32_t index) const;
    inline       Scalar&  operator[](uint32_t index);
    inline const Scalar&  operator[](uint32_t index) const;
    // sign
    inline       Vector2& changeSign(bool cx=true, bool cy=true);
    inline const Vector2  changeSigned(bool cx=true, bool cy=true) const;
    inline const Vector2  operator-() const;
    // with other
    inline const Vector2  operator+(const Vector2 &b) const;
    inline const Vector2  operator-(const Vector2 &b) const;
    inline const Vector2  operator*(const Vector2 &b) const;
    inline const Vector2  operator/(const Vector2 &b) const;
    inline const Vector2  operator*(Scalar b)         const;
    inline const Vector2  operator/(Scalar b)         const;
    inline       Vector2& operator+=(const Vector2 &b);
    inline       Vector2& operator-=(const Vector2 &b);
    inline       Vector2& operator*=(const Vector2 &b);
    inline       Vector2& operator/=(const Vector2 &b);
    inline       Vector2& operator*=(Scalar b);
    inline       Vector2& operator/=(Scalar b);
    // length
    inline       Scalar   length() const;
    inline       Vector2& normalize();
    inline const Vector2  normalized() const;
    // compare element wise
    inline bool operator==(const Vector2 &b) const;
    inline bool operator!=(const Vector2 &b) const;
    inline bool operator<=(const Vector2 &b) const;
    inline bool operator>=(const Vector2 &b) const;
    inline bool operator< (const Vector2 &b) const;
    inline bool operator> (const Vector2 &b) const;
};
// static arithmetics
template<class Scalar> inline const Vector2<Scalar> Floor(const Vector2<Scalar> &a);
template<class Scalar> inline const Vector2<Scalar> Sqrt(const Vector2<Scalar> &a);
template<class Scalar> inline const Vector2<Scalar> operator*(Scalar scale, const Vector2<Scalar> &a);
template<class Scalar> inline const Scalar  Dot(const Vector2<Scalar> &a, const Vector2<Scalar> &b);
template<class Scalar> inline const Scalar  Cross(const Vector2<Scalar> &a, const Vector2<Scalar> &b);
// stream
template<class Scalar, class ostream> inline ostream &operator<<(ostream &out, const Vector2<Scalar> &a);

}