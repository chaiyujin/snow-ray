#pragma once
#include "base.h"
#include "vec.h"

/* ====================
   _Vector4 Declaration
   ==================== */
namespace snowrt {

template <class Scalar>
struct ALIGNED(16) _Vector4 {
    union {
        Scalar data[4];
        struct { Scalar x, y, z, w; };
    };
    inline _Vector4();
    inline _Vector4(const _Vector4& b);
    inline explicit _Vector4(Scalar a);
    inline explicit _Vector4(Scalar a, Scalar b);
    inline explicit _Vector4(Scalar a, Scalar b, Scalar c);
    inline explicit _Vector4(Scalar a, Scalar b, Scalar c, Scalar d);
    inline explicit _Vector4(const _Vector2<Scalar> &xy);
    inline explicit _Vector4(const _Vector3<Scalar> &xyz);
    inline explicit _Vector4(const Scalar *ptr);
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
    inline       _Vector4& changeSign(bool cx=true, bool cy=true, bool cz=true, bool cw=true);
    inline const _Vector4  changeSigned(bool cx=true, bool cy=true, bool cz=true, bool cw=true) const;
    inline const _Vector4  operator-() const;
    // with other
    inline const _Vector4  operator+(const _Vector4 &b) const;
    inline const _Vector4  operator-(const _Vector4 &b) const;
    inline const _Vector4  operator*(const _Vector4 &b) const;
    inline const _Vector4  operator/(const _Vector4 &b) const;
    inline const _Vector4  operator*(Scalar b)         const;
    inline const _Vector4  operator/(Scalar b)         const;
    inline       _Vector4& operator+=(const _Vector4 &b);
    inline       _Vector4& operator-=(const _Vector4 &b);
    inline       _Vector4& operator*=(const _Vector4 &b);
    inline       _Vector4& operator/=(const _Vector4 &b);
    inline       _Vector4& operator*=(Scalar b);
    inline       _Vector4& operator/=(Scalar b);
    // length
    inline       Scalar   length() const;
    inline       _Vector4& normalize();
    inline const _Vector4  normalized() const;
    // compare element wise
    inline bool operator==(const _Vector4 &b) const;
    inline bool operator!=(const _Vector4 &b) const;
    inline bool operator<=(const _Vector4 &b) const;
    inline bool operator>=(const _Vector4 &b) const;
    inline bool operator< (const _Vector4 &b) const;
    inline bool operator> (const _Vector4 &b) const;
};
// static arithmetics
template <class Scalar> inline const _Vector4<Scalar> Floor(const _Vector4<Scalar> &a);
template <class Scalar> inline const _Vector4<Scalar> Sqrt(const _Vector4<Scalar> &a);
template <class Scalar> inline const _Vector4<Scalar> operator*(Scalar scale, const _Vector4<Scalar> &a);
template <class Scalar> inline const Scalar          Dot3(const _Vector4<Scalar> &a, const _Vector4<Scalar> &b);
template <class Scalar> inline const _Vector4<Scalar> Cross3(const _Vector4<Scalar> &a, const _Vector4<Scalar> &b);
// stream
template <class Scalar, class ostream> inline ostream &operator<<(ostream &out, const _Vector4<Scalar> &a);

}

/* ===================
   _Vector4 Definition
   =================== */
namespace snowrt {

template <class Scalar> inline _Vector4<Scalar>::_Vector4(): x(0), y(0), z(0), w(0) {}
template <class Scalar> inline _Vector4<Scalar>::_Vector4(const _Vector4<Scalar>& b): x(b.x), y(b.y), z(b.z), w(b.w) {}
template <class Scalar> inline _Vector4<Scalar>::_Vector4(Scalar a): x(a), y(0), z(0), w(0) {}
template <class Scalar> inline _Vector4<Scalar>::_Vector4(Scalar a, Scalar b): x(a), y(b), z(0), w(0) {}
template <class Scalar> inline _Vector4<Scalar>::_Vector4(Scalar a, Scalar b, Scalar c): x(a), y(b), z(c), w(0) {}
template <class Scalar> inline _Vector4<Scalar>::_Vector4(Scalar a, Scalar b, Scalar c, Scalar d): x(a), y(b), z(c), w(d) {}
template <class Scalar> inline _Vector4<Scalar>::_Vector4(const _Vector2<Scalar> &xy):  x(xy.x),  y(xy.y),  z(0),     w(0) {}
template <class Scalar> inline _Vector4<Scalar>::_Vector4(const _Vector3<Scalar> &xyz): x(xyz.x), y(xyz.y), z(xyz.z), w(0) {}
template <class Scalar> inline _Vector4<Scalar>::_Vector4(const Scalar *ptr): x(ptr[0]), y(ptr[1]), z(ptr[2]), w(ptr[3])  {}

// check finite
template <class Scalar> inline bool _Vector4<Scalar>::isnan()    const { return std::isnan(x) || std::isnan(y) || std::isnan(z) || std::isnan(w); }
template <class Scalar> inline bool _Vector4<Scalar>::isinf()    const { return std::isinf(x) || std::isinf(y) || std::isinf(z) || std::isinf(w); }
template <class Scalar> inline bool _Vector4<Scalar>::isfinite() const { return std::isfinite(x) && std::isfinite(y) && std::isfinite(z) && std::isfinite(w); }
// indexing
template <class Scalar> inline       Scalar&  _Vector4<Scalar>::at(uint32_t index)               { return data[index]; }
template <class Scalar> inline const Scalar&  _Vector4<Scalar>::at(uint32_t index)         const { return data[index]; }
template <class Scalar> inline       Scalar&  _Vector4<Scalar>::operator[](uint32_t index)       { return data[index]; }
template <class Scalar> inline const Scalar&  _Vector4<Scalar>::operator[](uint32_t index) const { return data[index]; }
// sign
template <class Scalar> inline _Vector4<Scalar>& _Vector4<Scalar>::changeSign(bool cx, bool cy, bool cz, bool cw) {
    if (cx) x=-x; if (cy) y=-y; if (cz) z=-z; if (cw) w=-w;
    return *this;
}
template <class Scalar> inline const _Vector4<Scalar> _Vector4<Scalar>::changeSigned(bool cx, bool cy, bool cz, bool cw) const {
    return _Vector4<Scalar>((cx)?-x:x, (cy)?-y:y, (cz)?-z:z, (cw)?-w:w);
}
template <class Scalar> inline const _Vector4<Scalar> _Vector4<Scalar>::operator-() const {
    return _Vector4<Scalar>(-x, -y, -z, -w);
}
// with other
template <class Scalar> inline const _Vector4<Scalar>  _Vector4<Scalar>::operator+(const _Vector4<Scalar> &b) const {
    return _Vector4<Scalar>(x+b.x, y+b.y, z+b.z, w+b.w);
}
template <class Scalar> inline const _Vector4<Scalar>  _Vector4<Scalar>::operator-(const _Vector4<Scalar> &b) const {
    return _Vector4<Scalar>(x-b.x, y-b.y, z-b.z, w-b.w);
}
template <class Scalar> inline const _Vector4<Scalar>  _Vector4<Scalar>::operator*(const _Vector4<Scalar> &b) const {
    return _Vector4<Scalar>(x*b.x, y*b.y, z*b.z, w*b.w);
}
template <class Scalar> inline const _Vector4<Scalar>  _Vector4<Scalar>::operator/(const _Vector4<Scalar> &b) const {
    return _Vector4<Scalar>(x/b.x, y/b.y, z/b.z, w/b.w);
}
template <class Scalar> inline const _Vector4<Scalar>  _Vector4<Scalar>::operator*(Scalar b) const {
    return _Vector4<Scalar>(x*b, y*b, z*b, w*b);
}
template <class Scalar> inline const _Vector4<Scalar>  _Vector4<Scalar>::operator/(Scalar b) const {
    Scalar invb = (Scalar)1/b;
    return _Vector4<Scalar>(x*invb, y*invb, z*invb, w*invb);
}
template <class Scalar> inline _Vector4<Scalar>& _Vector4<Scalar>::operator+=(const _Vector4<Scalar> &b) {
    x += b.x; y += b.y;
    z += b.z; w += b.w;
    return *this;
}
template <class Scalar> inline _Vector4<Scalar>& _Vector4<Scalar>::operator-=(const _Vector4<Scalar> &b) {
    x -= b.x; y -= b.y;
    z -= b.z; w -= b.w;
    return *this;    
}
template <class Scalar> inline _Vector4<Scalar>& _Vector4<Scalar>::operator*=(const _Vector4<Scalar> &b) {
    x *= b.x; y *= b.y;
    z *= b.z; w *= b.w;
    return *this;
}
template <class Scalar> inline _Vector4<Scalar>& _Vector4<Scalar>::operator/=(const _Vector4<Scalar> &b) {
    x /= b.x; y /= b.y;
    z /= b.z; w /= b.w;
    return *this;
}
template <class Scalar> inline _Vector4<Scalar>& _Vector4<Scalar>::operator*=(Scalar b) {
    x *= b; y *= b;
    z *= b; w *= b;
    return *this;
}
template <class Scalar> inline _Vector4<Scalar>& _Vector4<Scalar>::operator/=(Scalar b) {
    Scalar invb = (Scalar)1/b;
    x *= invb; y *= invb;
    z *= invb; w *= invb;
    return *this;
}
    // length
template <class Scalar> inline Scalar _Vector4<Scalar>::length() const {
    return std::sqrt(x*x+y*y+z*z+w*w);
}
template <class Scalar> inline _Vector4<Scalar>& _Vector4<Scalar>::normalize() {
    *this /= length();
    return *this;
}
template <class Scalar> inline const _Vector4<Scalar>  _Vector4<Scalar>::normalized() const {
    return *this / length();
}
    // compare element wise
template <class Scalar> inline bool _Vector4<Scalar>::operator==(const _Vector4<Scalar> &b) const {
    return (x==b.x)&&(y==b.y)&&(z==b.z)&&(w==b.w);
}
template <class Scalar> inline bool _Vector4<Scalar>::operator!=(const _Vector4<Scalar> &b) const {
    return !(*this == b);
}
template <class Scalar> inline bool _Vector4<Scalar>::operator<=(const _Vector4<Scalar> &b) const {
    return (x<=b.x)&&(y<=b.y)&&(z<=b.z)&&(w<=b.w);
}
template <class Scalar> inline bool _Vector4<Scalar>::operator>=(const _Vector4<Scalar> &b) const {
    return (x>=b.x)&&(y>=b.y)&&(z>=b.z)&&(w>=b.w);
}
template <class Scalar> inline bool _Vector4<Scalar>::operator< (const _Vector4<Scalar> &b) const {
    return (x< b.x)&&(y< b.y)&&(z< b.z)&&(w< b.w);
}
template <class Scalar> inline bool _Vector4<Scalar>::operator> (const _Vector4<Scalar> &b) const {
    return (x> b.x)&&(y> b.y)&&(z> b.z)&&(w> b.w);    
}

// static arithmetics
template <class Scalar> inline const _Vector4<Scalar> Floor(const _Vector4<Scalar> &a) {
    return _Vector4<Scalar>(std::floor(a.x), std::floor(a.y), std::floor(a.z), std::floor(a.w));
}
template <class Scalar> inline const _Vector4<Scalar> Sqrt(const _Vector4<Scalar> &a) {
    return _Vector4<Scalar>(std::sqrt(a.x), std::sqrt(a.y), std::sqrt(a.z), std::sqrt(a.w));
}
template <class Scalar> inline const _Vector4<Scalar> operator*(Scalar scale, const _Vector4<Scalar> &a) {
    return a * scale;
}
template <class Scalar> inline const Scalar Dot3(const _Vector4<Scalar> &a, const _Vector4<Scalar> &b) {
    return a.x*b.x + a.y*b.y + a.z*b.z;
}
template <class Scalar> inline const _Vector4<Scalar> Cross3(const _Vector4<Scalar> &a, const _Vector4<Scalar> &b) {
    return _Vector4<Scalar>(
        a.y*b.z-a.z*b.y,
        a.z*b.x-a.x*b.z,
        a.x*b.y-a.y*b.x,
        0
    );
}
// stream
template <class Scalar, class ostream> inline ostream &operator<<(ostream &out, const _Vector4<Scalar> &a) {
    out << "vec4<" << typeid(Scalar).name() << ">: [" << a.x << ", " << a.y << ", " << a.z << ", " << a.w << "]";
    return out;
}

}