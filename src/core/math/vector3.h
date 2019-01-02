#pragma once
#include "base.h"
#include "vector2_impl.h"
#include <iostream>

namespace ray::math {

/**
 * Vector3
 * */
template <class Scalar>
struct ALIGNED(16) Vector3 {
    union {
        Scalar data[3];
        struct { Scalar x, y, z; };
    };
    inline Vector3();
    inline Vector3(const Vector3 &b);
    inline explicit Vector3(Scalar a);
    inline explicit Vector3(Scalar a, Scalar b);
    inline explicit Vector3(Scalar a, Scalar b, Scalar c);
    inline explicit Vector3(const Vector2<Scalar> &xy);
    inline explicit Vector3(const Scalar *ptr);
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
    inline       Vector3& changeSign(bool cx=true, bool cy=true, bool cz=true);
    inline const Vector3  changeSigned(bool cx=true, bool cy=true, bool cz=true) const;
    inline const Vector3  operator-() const;
    // with other
    inline const Vector3  operator+(const Vector3 &b) const;
    inline const Vector3  operator-(const Vector3 &b) const;
    inline const Vector3  operator*(const Vector3 &b) const;
    inline const Vector3  operator/(const Vector3 &b) const;
    inline const Vector3  operator*(Scalar b)         const;
    inline const Vector3  operator/(Scalar b)         const;
    inline       Vector3& operator+=(const Vector3 &b);
    inline       Vector3& operator-=(const Vector3 &b);
    inline       Vector3& operator*=(const Vector3 &b);
    inline       Vector3& operator/=(const Vector3 &b);
    inline       Vector3& operator*=(Scalar b);
    inline       Vector3& operator/=(Scalar b);
    // length
    inline       Scalar   length() const;
    inline       Vector3& normalize();
    inline const Vector3  normalized() const;
    // compare element wise
    inline bool operator==(const Vector3 &b) const;
    inline bool operator!=(const Vector3 &b) const;
    inline bool operator<=(const Vector3 &b) const;
    inline bool operator>=(const Vector3 &b) const;
    inline bool operator< (const Vector3 &b) const;
    inline bool operator> (const Vector3 &b) const;
};
// static arithmetics
template <class Scalar> inline const Vector3<Scalar> Floor(const Vector3<Scalar> &a);
template <class Scalar> inline const Vector3<Scalar> Sqrt(const Vector3<Scalar> &a);
template <class Scalar> inline const Vector3<Scalar> operator*(Scalar scale, const Vector3<Scalar> &a);
template <class Scalar> inline const Scalar          Dot(const Vector3<Scalar> &a, const Vector3<Scalar> &b);
template <class Scalar> inline const Vector3<Scalar> Cross(const Vector3<Scalar> &a, const Vector3<Scalar> &b);
// stream
template <class Scalar> inline std::ostream &operator<<(std::ostream &out, const Vector3<Scalar> &a);


}