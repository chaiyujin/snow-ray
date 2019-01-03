#pragma once
#include "vector3.h"
#include <typeinfo>


namespace snowray {
namespace math {


/**
 * Vector3<Scalar> implemention
 * */

template <class Scalar> inline Vector3<Scalar>::Vector3() : x(0), y(0), z(0) {}
template <class Scalar> inline Vector3<Scalar>::Vector3(const Vector3<Scalar> &b) : x(b.x), y(b.y), z(b.z) {}
template <class Scalar> inline Vector3<Scalar>::Vector3(Scalar a) : x(a), y(0), z(0) {}
template <class Scalar> inline Vector3<Scalar>::Vector3(Scalar a, Scalar b) : x(a), y(b), z(0) {}
template <class Scalar> inline Vector3<Scalar>::Vector3(Scalar a, Scalar b, Scalar c) : x(a), y(b), z(c) {}
template <class Scalar> inline Vector3<Scalar>::Vector3(const Vector2<Scalar> &xy) : x(xy.x), y(xy.y), z(0) {}
template <class Scalar> inline Vector3<Scalar>::Vector3(const Scalar *ptr) : x(ptr[0]), y(ptr[1]), z(ptr[2]) {}
// check finite
template <class Scalar> inline bool Vector3<Scalar>::isnan()    const { return std::isnan(x) || std::isnan(y) || std::isnan(z); }
template <class Scalar> inline bool Vector3<Scalar>::isinf()    const { return std::isinf(x) || std::isinf(y) || std::isinf(z); }
template <class Scalar> inline bool Vector3<Scalar>::isfinite() const { return std::isfinite(x) && std::isfinite(y) && std::isfinite(z); }
// indexing
template <class Scalar> inline       Scalar&  Vector3<Scalar>::at(uint32_t index)               { return data[index]; }
template <class Scalar> inline const Scalar&  Vector3<Scalar>::at(uint32_t index)         const { return data[index]; }
template <class Scalar> inline       Scalar&  Vector3<Scalar>::operator[](uint32_t index)       { return data[index]; }
template <class Scalar> inline const Scalar&  Vector3<Scalar>::operator[](uint32_t index) const { return data[index]; }
// sign
template <class Scalar> inline       Vector3<Scalar>& Vector3<Scalar>::changeSign(bool cx, bool cy, bool cz)         { if (cx) x=-x; if (cy) y=-y; if (cz) z=-z; return *this; }
template <class Scalar> inline const Vector3<Scalar>  Vector3<Scalar>::changeSigned(bool cx, bool cy, bool cz) const { return Vector3<Scalar>((cx)?-x:x, (cy)?-y:y, (cz)?-z:z); }
template <class Scalar> inline const Vector3<Scalar>  Vector3<Scalar>::operator-() const { return Vector3<Scalar>(-x, -y, -z); }
// with other
template <class Scalar> inline const Vector3<Scalar>  Vector3<Scalar>::operator+(const Vector3<Scalar> &b) const { return Vector3<Scalar>(x+b.x, y+b.y, z+b.z); }
template <class Scalar> inline const Vector3<Scalar>  Vector3<Scalar>::operator-(const Vector3<Scalar> &b) const { return Vector3<Scalar>(x-b.x, y-b.y, z-b.z); }
template <class Scalar> inline const Vector3<Scalar>  Vector3<Scalar>::operator*(const Vector3<Scalar> &b) const { return Vector3<Scalar>(x*b.x, y*b.y, z*b.z); }
template <class Scalar> inline const Vector3<Scalar>  Vector3<Scalar>::operator/(const Vector3<Scalar> &b) const { return Vector3<Scalar>(x/b.x, y/b.y, z/b.z); }
template <class Scalar> inline const Vector3<Scalar>  Vector3<Scalar>::operator*(Scalar b)         const { return Vector3<Scalar>(x*b,   y*b,   z*b);   }
template <class Scalar> inline const Vector3<Scalar>  Vector3<Scalar>::operator/(Scalar b)         const { Scalar invb=(Scalar)1/b; return Vector3<Scalar>(x*invb, y*invb, z*invb); }
template <class Scalar> inline       Vector3<Scalar>& Vector3<Scalar>::operator+=(const Vector3<Scalar> &b)      { x+=b.x; y+=b.y; z+=b.z; return *this; }
template <class Scalar> inline       Vector3<Scalar>& Vector3<Scalar>::operator-=(const Vector3<Scalar> &b)      { x-=b.x; y-=b.y; z-=b.z; return *this; }
template <class Scalar> inline       Vector3<Scalar>& Vector3<Scalar>::operator*=(const Vector3<Scalar> &b)      { x*=b.x; y*=b.y; z*=b.z; return *this; }
template <class Scalar> inline       Vector3<Scalar>& Vector3<Scalar>::operator/=(const Vector3<Scalar> &b)      { x/=b.x; y/=b.y; z/=b.z; return *this; }
template <class Scalar> inline       Vector3<Scalar>& Vector3<Scalar>::operator*=(Scalar b)              { x*=b;   y*=b;   z*=b;   return *this; }
template <class Scalar> inline       Vector3<Scalar>& Vector3<Scalar>::operator/=(Scalar b)              { *this *= (Scalar)1/b;    return *this; }
// length
template <class Scalar> inline       Scalar   Vector3<Scalar>::length()     const { return std::sqrt(x*x+y*y+z*z);   }
template <class Scalar> inline       Vector3<Scalar>& Vector3<Scalar>::normalize()        { *this /= length(); return *this; }
template <class Scalar> inline const Vector3<Scalar>  Vector3<Scalar>::normalized() const { return *this / length();         }
// compare element wise
template <class Scalar> inline bool Vector3<Scalar>::operator==(const Vector3<Scalar> &b) const { return (x==b.x)&&(y==b.y)&&(z==b.z); }
template <class Scalar> inline bool Vector3<Scalar>::operator!=(const Vector3<Scalar> &b) const { return !(*this==b);                  }
template <class Scalar> inline bool Vector3<Scalar>::operator<=(const Vector3<Scalar> &b) const { return (x<=b.x)&&(y<=b.y)&&(z<=b.z); }
template <class Scalar> inline bool Vector3<Scalar>::operator>=(const Vector3<Scalar> &b) const { return (x>=b.x)&&(y>=b.y)&&(z>=b.z); }
template <class Scalar> inline bool Vector3<Scalar>::operator< (const Vector3<Scalar> &b) const { return (x< b.x)&&(y< b.y)&&(z< b.z); }
template <class Scalar> inline bool Vector3<Scalar>::operator> (const Vector3<Scalar> &b) const { return (x> b.x)&&(y> b.y)&&(z> b.z); }
    
// static arithmetics
template <class Scalar> inline const Vector3<Scalar> Floor(const Vector3<Scalar> &a) { return Vector3<Scalar>(std::floor(a.x), std::floor(a.y), std::floor(a.z)); }
template <class Scalar> inline const Vector3<Scalar> Sqrt(const Vector3<Scalar> &a)  { return Vector3<Scalar>(std::sqrt(a.x),  std::sqrt(a.y),  std::sqrt(a.z));  }
template <class Scalar> inline const Vector3<Scalar> operator*(Scalar scale, const Vector3<Scalar> &a) { return a * scale; }
template <class Scalar> inline const Scalar  Dot(const Vector3<Scalar> &a, const Vector3<Scalar> &b) { return a.x*b.x+a.y*b.y+a.z*b.z; }
template <class Scalar> inline const Vector3<Scalar> Cross(const Vector3<Scalar> &a, const Vector3<Scalar> &b) {
    return Vector3<Scalar>(
        a.y*b.z-a.z*b.y,
        a.z*b.x-a.x*b.z,
        a.x*b.y-a.y*b.x
    );
}
// stream
template <class Scalar, class ostream> inline ostream &operator<<(ostream &out, const Vector3<Scalar> &a) {
    out << "vec3<" << typeid(Scalar).name() << ">: [" << a.x << ", " << a.y << ", " << a.z << "]";
    return out;
}

typedef Vector3<Float>    Float3;
typedef Vector3<int32_t>  Int3;
typedef Vector3<uint32_t> UInt3;

}
}