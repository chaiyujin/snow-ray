#pragma once
#include "vector2.h"
#include <typeinfo>

namespace snowray::math {

/**
 * Float2 implemention
 * */

template<class Scalar> inline Vector2<Scalar>::Vector2() : x(0), y(0) {}
template<class Scalar> inline Vector2<Scalar>::Vector2(Scalar a) : x(a), y(0) {}
template<class Scalar> inline Vector2<Scalar>::Vector2(Scalar a, Scalar b) : x(a), y(b) {}
template<class Scalar> inline Vector2<Scalar>::Vector2(const Vector2<Scalar> &b)  : x(b.x), y(b.y) {}
template<class Scalar> inline Vector2<Scalar>::Vector2(const Scalar *ptr) : x(ptr[0]), y(ptr[1]) {}

template<class Scalar> inline bool Vector2<Scalar>::isnan() const { return std::isnan(x) || std::isnan(y); }
template<class Scalar> inline bool Vector2<Scalar>::isinf() const { return std::isinf(x) || std::isinf(y); }
template<class Scalar> inline bool Vector2<Scalar>::isfinite() const { return std::isfinite(x) && std::isfinite(y); }

template<class Scalar> inline       Scalar&  Vector2<Scalar>::at(uint32_t index)               { return data[index]; }
template<class Scalar> inline const Scalar&  Vector2<Scalar>::at(uint32_t index)         const { return data[index]; }
template<class Scalar> inline       Scalar&  Vector2<Scalar>::operator[](uint32_t index)       { return data[index]; }
template<class Scalar> inline const Scalar&  Vector2<Scalar>::operator[](uint32_t index) const { return data[index]; }

template<class Scalar> inline       Vector2<Scalar>& Vector2<Scalar>::changeSign(bool cx, bool cy)         { if (cx) x = -x; if (cy) y = -y; return *this; }
template<class Scalar> inline const Vector2<Scalar>  Vector2<Scalar>::changeSigned(bool cx, bool cy) const { return Vector2<Scalar>((cx)?-x:x, (cy)?-y:y); }
template<class Scalar> inline const Vector2<Scalar>  Vector2<Scalar>::operator-()                    const { return Vector2<Scalar>(-x, -y); }

template<class Scalar> inline const Vector2<Scalar>  Vector2<Scalar>::operator+(const Vector2<Scalar> &b) const { return Vector2<Scalar>(x+b.x, y+b.y); }
template<class Scalar> inline const Vector2<Scalar>  Vector2<Scalar>::operator-(const Vector2<Scalar> &b) const { return Vector2<Scalar>(x-b.x, y-b.y); }
template<class Scalar> inline const Vector2<Scalar>  Vector2<Scalar>::operator*(const Vector2<Scalar> &b) const { return Vector2<Scalar>(x*b.x, y*b.y); }
template<class Scalar> inline const Vector2<Scalar>  Vector2<Scalar>::operator/(const Vector2<Scalar> &b) const { return Vector2<Scalar>(x/b.x, y/b.y); }
template<class Scalar> inline const Vector2<Scalar>  Vector2<Scalar>::operator*(Scalar b)         const { return Vector2<Scalar>(x*b, y*b);     }
template<class Scalar> inline const Vector2<Scalar>  Vector2<Scalar>::operator/(Scalar b)         const { Scalar invb = (Scalar)1/b; return Vector2<Scalar>(x*invb, y*invb); }

template<class Scalar> inline       Vector2<Scalar>& Vector2<Scalar>::operator+=(const Vector2<Scalar> &b) { x += b.x; y += b.y; return *this; }
template<class Scalar> inline       Vector2<Scalar>& Vector2<Scalar>::operator-=(const Vector2<Scalar> &b) { x -= b.x; y -= b.y; return *this; }
template<class Scalar> inline       Vector2<Scalar>& Vector2<Scalar>::operator*=(const Vector2<Scalar> &b) { x *= b.x; y *= b.y; return *this; }
template<class Scalar> inline       Vector2<Scalar>& Vector2<Scalar>::operator/=(const Vector2<Scalar> &b) { x /= b.x; y /= b.y; return *this; }
template<class Scalar> inline       Vector2<Scalar>& Vector2<Scalar>::operator*=(Scalar b)         { x *= b; y *= b; return *this;     }
template<class Scalar> inline       Vector2<Scalar>& Vector2<Scalar>::operator/=(Scalar b)         { Scalar invb = (Scalar)1/b; x *= invb; y *= invb; return *this; }

template<class Scalar> inline       Scalar   Vector2<Scalar>::length()     const { return std::sqrt(x*x+y*y); }
template<class Scalar> inline       Vector2<Scalar>& Vector2<Scalar>::normalize()        { *this /= length(); return *this; }
template<class Scalar> inline const Vector2<Scalar>  Vector2<Scalar>::normalized() const { return *this / length(); }

template<class Scalar> inline bool Vector2<Scalar>::operator==(const Vector2<Scalar> &b) const { return (x==b.x) && (y==b.y); }
template<class Scalar> inline bool Vector2<Scalar>::operator!=(const Vector2<Scalar> &b) const { return !(*this==b);          }
template<class Scalar> inline bool Vector2<Scalar>::operator<=(const Vector2<Scalar> &b) const { return (x<=b.x) && (y<=b.y); }
template<class Scalar> inline bool Vector2<Scalar>::operator>=(const Vector2<Scalar> &b) const { return (x>=b.x) && (y>=b.y); }
template<class Scalar> inline bool Vector2<Scalar>::operator< (const Vector2<Scalar> &b) const { return (x< b.x) && (y< b.y); }
template<class Scalar> inline bool Vector2<Scalar>::operator> (const Vector2<Scalar> &b) const { return (x> b.x) && (y> b.y); }

// static arithmetics
template<class Scalar> inline const Vector2<Scalar> Floor(const Vector2<Scalar> &a) { return Vector2<Scalar>(std::floor(a.x), std::floor(a.y)); }
template<class Scalar> inline const Vector2<Scalar> Sqrt(const Vector2<Scalar> &a)  { return Vector2<Scalar>(std::sqrt(a.x),  std::sqrt(a.y));  }
template<class Scalar> inline const Vector2<Scalar> operator*(Scalar scale, const Vector2<Scalar> &a) { return a * scale; }
template<class Scalar> inline const Scalar  Dot(const Vector2<Scalar> &a, const Vector2<Scalar> &b)   { return a.x * b.x + a.y * b.y; }
template<class Scalar> inline const Scalar  Cross(const Vector2<Scalar> &a, const Vector2<Scalar> &b) { return a.x * b.y - a.y * b.x; }

template<class Scalar, class ostream> inline ostream &operator<<(ostream &out, const Vector2<Scalar> &a) {
    out << "vec2<" << typeid(Scalar).name() << ">: [" << a.x << ", " << a.y << "]";
    return out;
}

typedef Vector2<Float>    Float2;
typedef Vector2<int32_t>  Int2;
typedef Vector2<uint32_t> UInt2;

}
