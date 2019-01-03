#pragma once
#include "base.h"
#include "vector2.h"
#include "vector3.h"

namespace snowray::math {

template <class Scalar>
struct ALIGNED(16) Vector4 {
    union {
        Scalar data[4];
        struct { Scalar x, y, z, w; };
    };
    inline Vector4();
    inline Vector4(const Vector4& b);
    inline explicit Vector4(Scalar a);
    inline explicit Vector4(Scalar a, Scalar b);
    inline explicit Vector4(Scalar a, Scalar b, Scalar c);
    inline explicit Vector4(Scalar a, Scalar b, Scalar c, Scalar d);
    inline explicit Vector4(const Vector2<Scalar> &xy);
    inline explicit Vector4(const Vector3<Scalar> &xyz);
    inline explicit Vector4(const Scalar *ptr);
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
    inline       Vector4& changeSign(bool cx=true, bool cy=true, bool cz=true, bool cw=true);
    inline const Vector4  changeSigned(bool cx=true, bool cy=true, bool cz=true, bool cw=true) const;
    inline const Vector4  operator-() const;
    // with other
    inline const Vector4  operator+(const Vector4 &b) const;
    inline const Vector4  operator-(const Vector4 &b) const;
    inline const Vector4  operator*(const Vector4 &b) const;
    inline const Vector4  operator/(const Vector4 &b) const;
    inline const Vector4  operator*(Scalar b)         const;
    inline const Vector4  operator/(Scalar b)         const;
    inline       Vector4& operator+=(const Vector4 &b);
    inline       Vector4& operator-=(const Vector4 &b);
    inline       Vector4& operator*=(const Vector4 &b);
    inline       Vector4& operator/=(const Vector4 &b);
    inline       Vector4& operator*=(Scalar b);
    inline       Vector4& operator/=(Scalar b);
    // length
    inline       Scalar   length() const;
    inline       Vector4& normalize();
    inline const Vector4  normalized() const;
    // compare element wise
    inline bool operator==(const Vector4 &b) const;
    inline bool operator!=(const Vector4 &b) const;
    inline bool operator<=(const Vector4 &b) const;
    inline bool operator>=(const Vector4 &b) const;
    inline bool operator< (const Vector4 &b) const;
    inline bool operator> (const Vector4 &b) const;
};
// static arithmetics
template <class Scalar> inline const Vector4<Scalar> Floor(const Vector4<Scalar> &a);
template <class Scalar> inline const Vector4<Scalar> Sqrt(const Vector4<Scalar> &a);
template <class Scalar> inline const Vector4<Scalar> operator*(Scalar scale, const Vector4<Scalar> &a);
template <class Scalar> inline const Scalar          Dot3(const Vector4<Scalar> &a, const Vector4<Scalar> &b);
template <class Scalar> inline const Vector4<Scalar> Cross3(const Vector4<Scalar> &a, const Vector4<Scalar> &b);
// stream
template <class Scalar, class ostream> inline ostream &operator<<(ostream &out, const Vector4<Scalar> &a);

}