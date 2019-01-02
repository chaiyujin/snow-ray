#pragma once
#include "vector4.h"

namespace snowray::math {

template <class Scalar> inline Vector4<Scalar>::Vector4(): x(0), y(0), z(0), w(0) {}
template <class Scalar> inline Vector4<Scalar>::Vector4(const Vector4<Scalar>& b): x(b.x), y(b.y), z(b.z), w(b.w) {}
template <class Scalar> inline Vector4<Scalar>::Vector4(Scalar a): x(a), y(0), z(0), w(0) {}
template <class Scalar> inline Vector4<Scalar>::Vector4(Scalar a, Scalar b): x(a), y(b), z(0), w(0) {}
template <class Scalar> inline Vector4<Scalar>::Vector4(Scalar a, Scalar b, Scalar c): x(a), y(b), z(c), w(0) {}
template <class Scalar> inline Vector4<Scalar>::Vector4(Scalar a, Scalar b, Scalar c, Scalar d): x(a), y(b), z(c), w(d) {}
template <class Scalar> inline Vector4<Scalar>::Vector4(const Vector2<Scalar> &xy):  x(xy.x),  y(xy.y),  z(0),     w(0) {}
template <class Scalar> inline Vector4<Scalar>::Vector4(const Vector3<Scalar> &xyz): x(xyz.x), y(xyz.y), z(xyz.z), w(0) {}
template <class Scalar> inline Vector4<Scalar>::Vector4(const Scalar *ptr): x(ptr[0]), y(ptr[1]), z(ptr[2]), w(ptr[3])  {}

// check finite
template <class Scalar> inline bool Vector4<Scalar>::isnan()    const { return std::isnan(x) || std::isnan(y) || std::isnan(z) || std::isnan(w); }
template <class Scalar> inline bool Vector4<Scalar>::isinf()    const { return std::isinf(x) || std::isinf(y) || std::isinf(z) || std::isinf(w); }
template <class Scalar> inline bool Vector4<Scalar>::isfinite() const { return std::isfinite(x) && std::isfinite(y) && std::isfinite(z) && std::isfinite(w); }
// indexing
template <class Scalar> inline       Scalar&  Vector4<Scalar>::at(uint32_t index)               { return data[index]; }
template <class Scalar> inline const Scalar&  Vector4<Scalar>::at(uint32_t index)         const { return data[index]; }
template <class Scalar> inline       Scalar&  Vector4<Scalar>::operator[](uint32_t index)       { return data[index]; }
template <class Scalar> inline const Scalar&  Vector4<Scalar>::operator[](uint32_t index) const { return data[index]; }
// sign
template <class Scalar> inline Vector4<Scalar>& Vector4<Scalar>::changeSign(bool cx, bool cy, bool cz, bool cw) {
    if (cx) x=-x; if (cy) y=-y; if (cz) z=-z; if (cw) w=-w;
    return *this;
}
template <class Scalar> inline const Vector4<Scalar> Vector4<Scalar>::changeSigned(bool cx, bool cy, bool cz, bool cw) const {
    return Vector4<Scalar>((cx)?-x:x, (cy)?-y:y, (cz)?-z:z, (cw)?-w:w);
}
template <class Scalar> inline const Vector4<Scalar> Vector4<Scalar>::operator-() const {
    return Vector4<Scalar>(-x, -y, -z, -w);
}
// with other
template <class Scalar> inline const Vector4<Scalar>  Vector4<Scalar>::operator+(const Vector4<Scalar> &b) const {
    return Vector4<Scalar>(x+b.x, y+b.y, z+b.z, w+b.w);
}
template <class Scalar> inline const Vector4<Scalar>  Vector4<Scalar>::operator-(const Vector4<Scalar> &b) const {
    return Vector4<Scalar>(x-b.x, y-b.y, z-b.z, w-b.w);
}
template <class Scalar> inline const Vector4<Scalar>  Vector4<Scalar>::operator*(const Vector4<Scalar> &b) const {
    return Vector4<Scalar>(x*b.x, y*b.y, z*b.z, w*b.w);
}
template <class Scalar> inline const Vector4<Scalar>  Vector4<Scalar>::operator/(const Vector4<Scalar> &b) const {
    return Vector4<Scalar>(x/b.x, y/b.y, z/b.z, w/b.w);
}
template <class Scalar> inline const Vector4<Scalar>  Vector4<Scalar>::operator*(Scalar b) const {
    return Vector4<Scalar>(x*b, y*b, z*b, w*b);
}
template <class Scalar> inline const Vector4<Scalar>  Vector4<Scalar>::operator/(Scalar b) const {
    Scalar invb = (Scalar)1/b;
    return Vector4<Scalar>(x*invb, y*invb, z*invb, w*invb);
}
template <class Scalar> inline Vector4<Scalar>& Vector4<Scalar>::operator+=(const Vector4<Scalar> &b) {
    x += b.x; y += b.y;
    z += b.z; w += b.w;
    return *this;
}
template <class Scalar> inline Vector4<Scalar>& Vector4<Scalar>::operator-=(const Vector4<Scalar> &b) {
    x -= b.x; y -= b.y;
    z -= b.z; w -= b.w;
    return *this;    
}
template <class Scalar> inline Vector4<Scalar>& Vector4<Scalar>::operator*=(const Vector4<Scalar> &b) {
    x *= b.x; y *= b.y;
    z *= b.z; w *= b.w;
    return *this;
}
template <class Scalar> inline Vector4<Scalar>& Vector4<Scalar>::operator/=(const Vector4<Scalar> &b) {
    x /= b.x; y /= b.y;
    z /= b.z; w /= b.w;
    return *this;
}
template <class Scalar> inline Vector4<Scalar>& Vector4<Scalar>::operator*=(Scalar b) {
    x *= b; y *= b;
    z *= b; w *= b;
    return *this;
}
template <class Scalar> inline Vector4<Scalar>& Vector4<Scalar>::operator/=(Scalar b) {
    Scalar invb = (Scalar)1/b;
    x *= invb; y *= invb;
    z *= invb; w *= invb;
    return *this;
}
    // length
template <class Scalar> inline Scalar Vector4<Scalar>::length() const {
    return std::sqrt(x*x+y*y+z*z+w*w);
}
template <class Scalar> inline Vector4<Scalar>& Vector4<Scalar>::normalize() {
    *this /= length();
    return *this;
}
template <class Scalar> inline const Vector4<Scalar>  Vector4<Scalar>::normalized() const {
    return *this / length();
}
    // compare element wise
template <class Scalar> inline bool Vector4<Scalar>::operator==(const Vector4<Scalar> &b) const {
    return (x==b.x)&&(y==b.y)&&(z==b.z)&&(w==b.w);
}
template <class Scalar> inline bool Vector4<Scalar>::operator!=(const Vector4<Scalar> &b) const {
    return !(*this == b);
}
template <class Scalar> inline bool Vector4<Scalar>::operator<=(const Vector4<Scalar> &b) const {
    return (x<=b.x)&&(y<=b.y)&&(z<=b.z)&&(w<=b.w);
}
template <class Scalar> inline bool Vector4<Scalar>::operator>=(const Vector4<Scalar> &b) const {
    return (x>=b.x)&&(y>=b.y)&&(z>=b.z)&&(w>=b.w);
}
template <class Scalar> inline bool Vector4<Scalar>::operator< (const Vector4<Scalar> &b) const {
    return (x< b.x)&&(y< b.y)&&(z< b.z)&&(w< b.w);
}
template <class Scalar> inline bool Vector4<Scalar>::operator> (const Vector4<Scalar> &b) const {
    return (x> b.x)&&(y> b.y)&&(z> b.z)&&(w> b.w);    
}

// static arithmetics
template <class Scalar> inline const Vector4<Scalar> Floor(const Vector4<Scalar> &a) {
    return Vector4<Scalar>(std::floor(a.x), std::floor(a.y), std::floor(a.z), std::floor(a.w));
}
template <class Scalar> inline const Vector4<Scalar> Sqrt(const Vector4<Scalar> &a) {
    return Vector4<Scalar>(std::sqrt(a.x), std::sqrt(a.y), std::sqrt(a.z), std::sqrt(a.w));
}
template <class Scalar> inline const Vector4<Scalar> operator*(Scalar scale, const Vector4<Scalar> &a) {
    return a * scale;
}

}