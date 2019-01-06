#pragma once
#include "base.h"
#include <typeinfo>

/* ====================
   _Vector2 Declaration
   ==================== */
namespace snowrt {

template <class Scalar>
struct ALIGNED(16) _Vector2 {
    union {
        Scalar data[2];
        struct { Scalar x, y; };
    };

    inline _Vector2();
    inline _Vector2(const _Vector2 &b);
    inline explicit _Vector2(Scalar a);
    inline explicit _Vector2(Scalar a, Scalar b);
    inline explicit _Vector2(const Scalar *ptr);
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
    inline       _Vector2& changeSign(bool cx=true, bool cy=true);
    inline const _Vector2  changeSigned(bool cx=true, bool cy=true) const;
    inline const _Vector2  operator-() const;
    // with other
    inline const _Vector2  operator+(const _Vector2 &b) const;
    inline const _Vector2  operator-(const _Vector2 &b) const;
    inline const _Vector2  operator*(const _Vector2 &b) const;
    inline const _Vector2  operator/(const _Vector2 &b) const;
    inline const _Vector2  operator*(Scalar b)         const;
    inline const _Vector2  operator/(Scalar b)         const;
    inline       _Vector2& operator+=(const _Vector2 &b);
    inline       _Vector2& operator-=(const _Vector2 &b);
    inline       _Vector2& operator*=(const _Vector2 &b);
    inline       _Vector2& operator/=(const _Vector2 &b);
    inline       _Vector2& operator*=(Scalar b);
    inline       _Vector2& operator/=(Scalar b);
    // length
    inline       Scalar   length() const;
    inline       _Vector2& normalize();
    inline const _Vector2  normalized() const;
    // compare element wise
    inline bool operator==(const _Vector2 &b) const;
    inline bool operator!=(const _Vector2 &b) const;
    inline bool operator<=(const _Vector2 &b) const;
    inline bool operator>=(const _Vector2 &b) const;
    inline bool operator< (const _Vector2 &b) const;
    inline bool operator> (const _Vector2 &b) const;
};
// static arithmetics
template<class Scalar> inline const _Vector2<Scalar> Floor(const _Vector2<Scalar> &a);
template<class Scalar> inline const _Vector2<Scalar> Sqrt(const _Vector2<Scalar> &a);
template<class Scalar> inline const _Vector2<Scalar> operator*(Scalar scale, const _Vector2<Scalar> &a);
template<class Scalar> inline const Scalar  Dot(const _Vector2<Scalar> &a, const _Vector2<Scalar> &b);
template<class Scalar> inline const Scalar  Cross(const _Vector2<Scalar> &a, const _Vector2<Scalar> &b);
// stream
template<class Scalar, class ostream> inline ostream &operator<<(ostream &out, const _Vector2<Scalar> &a);

}

/* ====================
   _Vector3 Declaration
   ==================== */
namespace snowrt {

template <class Scalar>
struct ALIGNED(16) _Vector3 {
    union {
        Scalar data[3];
        struct { Scalar x, y, z; };
    };
    inline _Vector3();
    inline _Vector3(const _Vector3 &b);
    inline explicit _Vector3(Scalar a);
    inline explicit _Vector3(Scalar a, Scalar b);
    inline explicit _Vector3(Scalar a, Scalar b, Scalar c);
    inline explicit _Vector3(const _Vector2<Scalar> &xy);
    inline explicit _Vector3(const Scalar *ptr);
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
    inline       _Vector3& changeSign(bool cx=true, bool cy=true, bool cz=true);
    inline const _Vector3  changeSigned(bool cx=true, bool cy=true, bool cz=true) const;
    inline const _Vector3  operator-() const;
    // with other
    inline const _Vector3  operator+(const _Vector3 &b) const;
    inline const _Vector3  operator-(const _Vector3 &b) const;
    inline const _Vector3  operator*(const _Vector3 &b) const;
    inline const _Vector3  operator/(const _Vector3 &b) const;
    inline const _Vector3  operator*(Scalar b)         const;
    inline const _Vector3  operator/(Scalar b)         const;
    inline       _Vector3& operator+=(const _Vector3 &b);
    inline       _Vector3& operator-=(const _Vector3 &b);
    inline       _Vector3& operator*=(const _Vector3 &b);
    inline       _Vector3& operator/=(const _Vector3 &b);
    inline       _Vector3& operator*=(Scalar b);
    inline       _Vector3& operator/=(Scalar b);
    // length
    inline       Scalar   length() const;
    inline       _Vector3& normalize();
    inline const _Vector3  normalized() const;
    // compare element wise
    inline bool operator==(const _Vector3 &b) const;
    inline bool operator!=(const _Vector3 &b) const;
    inline bool operator<=(const _Vector3 &b) const;
    inline bool operator>=(const _Vector3 &b) const;
    inline bool operator< (const _Vector3 &b) const;
    inline bool operator> (const _Vector3 &b) const;
};
// static arithmetics
template <class Scalar> inline const _Vector3<Scalar> Floor(const _Vector3<Scalar> &a);
template <class Scalar> inline const _Vector3<Scalar> Sqrt(const _Vector3<Scalar> &a);
template <class Scalar> inline const _Vector3<Scalar> operator*(Scalar scale, const _Vector3<Scalar> &a);
template <class Scalar> inline const Scalar          Dot(const _Vector3<Scalar> &a, const _Vector3<Scalar> &b);
template <class Scalar> inline const _Vector3<Scalar> Cross(const _Vector3<Scalar> &a, const _Vector3<Scalar> &b);
// stream
template <class Scalar, class ostream> inline ostream &operator<<(ostream &out, const _Vector3<Scalar> &a);

}

/* ===================
   _Vector2 Definition
   =================== */
namespace snowrt {

template<class Scalar> inline _Vector2<Scalar>::_Vector2() : x(0), y(0) {}
template<class Scalar> inline _Vector2<Scalar>::_Vector2(Scalar a) : x(a), y(0) {}
template<class Scalar> inline _Vector2<Scalar>::_Vector2(Scalar a, Scalar b) : x(a), y(b) {}
template<class Scalar> inline _Vector2<Scalar>::_Vector2(const _Vector2<Scalar> &b)  : x(b.x), y(b.y) {}
template<class Scalar> inline _Vector2<Scalar>::_Vector2(const Scalar *ptr) : x(ptr[0]), y(ptr[1]) {}

template<class Scalar> inline bool _Vector2<Scalar>::isnan() const { return std::isnan(x) || std::isnan(y); }
template<class Scalar> inline bool _Vector2<Scalar>::isinf() const { return std::isinf(x) || std::isinf(y); }
template<class Scalar> inline bool _Vector2<Scalar>::isfinite() const { return std::isfinite(x) && std::isfinite(y); }

template<class Scalar> inline       Scalar&  _Vector2<Scalar>::at(uint32_t index)               { return data[index]; }
template<class Scalar> inline const Scalar&  _Vector2<Scalar>::at(uint32_t index)         const { return data[index]; }
template<class Scalar> inline       Scalar&  _Vector2<Scalar>::operator[](uint32_t index)       { return data[index]; }
template<class Scalar> inline const Scalar&  _Vector2<Scalar>::operator[](uint32_t index) const { return data[index]; }

template<class Scalar> inline       _Vector2<Scalar>& _Vector2<Scalar>::changeSign(bool cx, bool cy)         { if (cx) x = -x; if (cy) y = -y; return *this; }
template<class Scalar> inline const _Vector2<Scalar>  _Vector2<Scalar>::changeSigned(bool cx, bool cy) const { return _Vector2<Scalar>((cx)?-x:x, (cy)?-y:y); }
template<class Scalar> inline const _Vector2<Scalar>  _Vector2<Scalar>::operator-()                    const { return _Vector2<Scalar>(-x, -y); }

template<class Scalar> inline const _Vector2<Scalar>  _Vector2<Scalar>::operator+(const _Vector2<Scalar> &b) const { return _Vector2<Scalar>(x+b.x, y+b.y); }
template<class Scalar> inline const _Vector2<Scalar>  _Vector2<Scalar>::operator-(const _Vector2<Scalar> &b) const { return _Vector2<Scalar>(x-b.x, y-b.y); }
template<class Scalar> inline const _Vector2<Scalar>  _Vector2<Scalar>::operator*(const _Vector2<Scalar> &b) const { return _Vector2<Scalar>(x*b.x, y*b.y); }
template<class Scalar> inline const _Vector2<Scalar>  _Vector2<Scalar>::operator/(const _Vector2<Scalar> &b) const { return _Vector2<Scalar>(x/b.x, y/b.y); }
template<class Scalar> inline const _Vector2<Scalar>  _Vector2<Scalar>::operator*(Scalar b)         const { return _Vector2<Scalar>(x*b, y*b);     }
template<class Scalar> inline const _Vector2<Scalar>  _Vector2<Scalar>::operator/(Scalar b)         const { Scalar invb = (Scalar)1/b; return _Vector2<Scalar>(x*invb, y*invb); }

template<class Scalar> inline       _Vector2<Scalar>& _Vector2<Scalar>::operator+=(const _Vector2<Scalar> &b) { x += b.x; y += b.y; return *this; }
template<class Scalar> inline       _Vector2<Scalar>& _Vector2<Scalar>::operator-=(const _Vector2<Scalar> &b) { x -= b.x; y -= b.y; return *this; }
template<class Scalar> inline       _Vector2<Scalar>& _Vector2<Scalar>::operator*=(const _Vector2<Scalar> &b) { x *= b.x; y *= b.y; return *this; }
template<class Scalar> inline       _Vector2<Scalar>& _Vector2<Scalar>::operator/=(const _Vector2<Scalar> &b) { x /= b.x; y /= b.y; return *this; }
template<class Scalar> inline       _Vector2<Scalar>& _Vector2<Scalar>::operator*=(Scalar b)         { x *= b; y *= b; return *this;     }
template<class Scalar> inline       _Vector2<Scalar>& _Vector2<Scalar>::operator/=(Scalar b)         { Scalar invb = (Scalar)1/b; x *= invb; y *= invb; return *this; }

template<class Scalar> inline       Scalar   _Vector2<Scalar>::length()     const { return std::sqrt(x*x+y*y); }
template<class Scalar> inline       _Vector2<Scalar>& _Vector2<Scalar>::normalize()        { *this /= length(); return *this; }
template<class Scalar> inline const _Vector2<Scalar>  _Vector2<Scalar>::normalized() const { return *this / length(); }

template<class Scalar> inline bool _Vector2<Scalar>::operator==(const _Vector2<Scalar> &b) const { return (x==b.x) && (y==b.y); }
template<class Scalar> inline bool _Vector2<Scalar>::operator!=(const _Vector2<Scalar> &b) const { return !(*this==b);          }
template<class Scalar> inline bool _Vector2<Scalar>::operator<=(const _Vector2<Scalar> &b) const { return (x<=b.x) && (y<=b.y); }
template<class Scalar> inline bool _Vector2<Scalar>::operator>=(const _Vector2<Scalar> &b) const { return (x>=b.x) && (y>=b.y); }
template<class Scalar> inline bool _Vector2<Scalar>::operator< (const _Vector2<Scalar> &b) const { return (x< b.x) && (y< b.y); }
template<class Scalar> inline bool _Vector2<Scalar>::operator> (const _Vector2<Scalar> &b) const { return (x> b.x) && (y> b.y); }

// static arithmetics
template<class Scalar> inline const _Vector2<Scalar> Floor(const _Vector2<Scalar> &a) { return _Vector2<Scalar>(std::floor(a.x), std::floor(a.y)); }
template<class Scalar> inline const _Vector2<Scalar> Sqrt(const _Vector2<Scalar> &a)  { return _Vector2<Scalar>(std::sqrt(a.x),  std::sqrt(a.y));  }
template<class Scalar> inline const _Vector2<Scalar> operator*(Scalar scale, const _Vector2<Scalar> &a) { return a * scale; }
template<class Scalar> inline const Scalar  Dot(const _Vector2<Scalar> &a, const _Vector2<Scalar> &b)   { return a.x * b.x + a.y * b.y; }
template<class Scalar> inline const Scalar  Cross(const _Vector2<Scalar> &a, const _Vector2<Scalar> &b) { return a.x * b.y - a.y * b.x; }

template<class Scalar, class ostream> inline ostream &operator<<(ostream &out, const _Vector2<Scalar> &a) {
    out << "vec2<" << typeid(Scalar).name() << ">: [" << a.x << ", " << a.y << "]";
    return out;
}

typedef _Vector2<Float>    Float2;
typedef _Vector2<int32_t>  Int2;
typedef _Vector2<uint32_t> UInt2;

}

/* ===================
   _Vector3 Definition
   =================== */
namespace snowrt {

template <class Scalar> inline _Vector3<Scalar>::_Vector3() : x(0), y(0), z(0) {}
template <class Scalar> inline _Vector3<Scalar>::_Vector3(const _Vector3<Scalar> &b) : x(b.x), y(b.y), z(b.z) {}
template <class Scalar> inline _Vector3<Scalar>::_Vector3(Scalar a) : x(a), y(0), z(0) {}
template <class Scalar> inline _Vector3<Scalar>::_Vector3(Scalar a, Scalar b) : x(a), y(b), z(0) {}
template <class Scalar> inline _Vector3<Scalar>::_Vector3(Scalar a, Scalar b, Scalar c) : x(a), y(b), z(c) {}
template <class Scalar> inline _Vector3<Scalar>::_Vector3(const _Vector2<Scalar> &xy) : x(xy.x), y(xy.y), z(0) {}
template <class Scalar> inline _Vector3<Scalar>::_Vector3(const Scalar *ptr) : x(ptr[0]), y(ptr[1]), z(ptr[2]) {}
// check finite
template <class Scalar> inline bool _Vector3<Scalar>::isnan()    const { return std::isnan(x) || std::isnan(y) || std::isnan(z); }
template <class Scalar> inline bool _Vector3<Scalar>::isinf()    const { return std::isinf(x) || std::isinf(y) || std::isinf(z); }
template <class Scalar> inline bool _Vector3<Scalar>::isfinite() const { return std::isfinite(x) && std::isfinite(y) && std::isfinite(z); }
// indexing
template <class Scalar> inline       Scalar&  _Vector3<Scalar>::at(uint32_t index)               { return data[index]; }
template <class Scalar> inline const Scalar&  _Vector3<Scalar>::at(uint32_t index)         const { return data[index]; }
template <class Scalar> inline       Scalar&  _Vector3<Scalar>::operator[](uint32_t index)       { return data[index]; }
template <class Scalar> inline const Scalar&  _Vector3<Scalar>::operator[](uint32_t index) const { return data[index]; }
// sign
template <class Scalar> inline       _Vector3<Scalar>& _Vector3<Scalar>::changeSign(bool cx, bool cy, bool cz)         { if (cx) x=-x; if (cy) y=-y; if (cz) z=-z; return *this; }
template <class Scalar> inline const _Vector3<Scalar>  _Vector3<Scalar>::changeSigned(bool cx, bool cy, bool cz) const { return _Vector3<Scalar>((cx)?-x:x, (cy)?-y:y, (cz)?-z:z); }
template <class Scalar> inline const _Vector3<Scalar>  _Vector3<Scalar>::operator-() const { return _Vector3<Scalar>(-x, -y, -z); }
// with other
template <class Scalar> inline const _Vector3<Scalar>  _Vector3<Scalar>::operator+(const _Vector3<Scalar> &b) const { return _Vector3<Scalar>(x+b.x, y+b.y, z+b.z); }
template <class Scalar> inline const _Vector3<Scalar>  _Vector3<Scalar>::operator-(const _Vector3<Scalar> &b) const { return _Vector3<Scalar>(x-b.x, y-b.y, z-b.z); }
template <class Scalar> inline const _Vector3<Scalar>  _Vector3<Scalar>::operator*(const _Vector3<Scalar> &b) const { return _Vector3<Scalar>(x*b.x, y*b.y, z*b.z); }
template <class Scalar> inline const _Vector3<Scalar>  _Vector3<Scalar>::operator/(const _Vector3<Scalar> &b) const { return _Vector3<Scalar>(x/b.x, y/b.y, z/b.z); }
template <class Scalar> inline const _Vector3<Scalar>  _Vector3<Scalar>::operator*(Scalar b)                 const { return _Vector3<Scalar>(x*b,   y*b,   z*b);   }
template <class Scalar> inline const _Vector3<Scalar>  _Vector3<Scalar>::operator/(Scalar b)                 const { Scalar invb=(Scalar)1/b; return _Vector3<Scalar>(x*invb, y*invb, z*invb); }
template <class Scalar> inline       _Vector3<Scalar>& _Vector3<Scalar>::operator+=(const _Vector3<Scalar> &b)      { x+=b.x; y+=b.y; z+=b.z; return *this; }
template <class Scalar> inline       _Vector3<Scalar>& _Vector3<Scalar>::operator-=(const _Vector3<Scalar> &b)      { x-=b.x; y-=b.y; z-=b.z; return *this; }
template <class Scalar> inline       _Vector3<Scalar>& _Vector3<Scalar>::operator*=(const _Vector3<Scalar> &b)      { x*=b.x; y*=b.y; z*=b.z; return *this; }
template <class Scalar> inline       _Vector3<Scalar>& _Vector3<Scalar>::operator/=(const _Vector3<Scalar> &b)      { x/=b.x; y/=b.y; z/=b.z; return *this; }
template <class Scalar> inline       _Vector3<Scalar>& _Vector3<Scalar>::operator*=(Scalar b)                      { x*=b;   y*=b;   z*=b;   return *this; }
template <class Scalar> inline       _Vector3<Scalar>& _Vector3<Scalar>::operator/=(Scalar b)                      { *this *= (Scalar)1/b;    return *this; }
// length
template <class Scalar> inline       Scalar   _Vector3<Scalar>::length()             const { return std::sqrt(x*x+y*y+z*z);   }
template <class Scalar> inline       _Vector3<Scalar>& _Vector3<Scalar>::normalize()        { *this /= length(); return *this; }
template <class Scalar> inline const _Vector3<Scalar>  _Vector3<Scalar>::normalized() const { return *this / length();         }
// compare element wise
template <class Scalar> inline bool _Vector3<Scalar>::operator==(const _Vector3<Scalar> &b) const { return (x==b.x)&&(y==b.y)&&(z==b.z); }
template <class Scalar> inline bool _Vector3<Scalar>::operator!=(const _Vector3<Scalar> &b) const { return !(*this==b);                  }
template <class Scalar> inline bool _Vector3<Scalar>::operator<=(const _Vector3<Scalar> &b) const { return (x<=b.x)&&(y<=b.y)&&(z<=b.z); }
template <class Scalar> inline bool _Vector3<Scalar>::operator>=(const _Vector3<Scalar> &b) const { return (x>=b.x)&&(y>=b.y)&&(z>=b.z); }
template <class Scalar> inline bool _Vector3<Scalar>::operator< (const _Vector3<Scalar> &b) const { return (x< b.x)&&(y< b.y)&&(z< b.z); }
template <class Scalar> inline bool _Vector3<Scalar>::operator> (const _Vector3<Scalar> &b) const { return (x> b.x)&&(y> b.y)&&(z> b.z); }
    
// static arithmetics
template <class Scalar> inline const _Vector3<Scalar> Floor(const _Vector3<Scalar> &a) { return _Vector3<Scalar>(std::floor(a.x), std::floor(a.y), std::floor(a.z)); }
template <class Scalar> inline const _Vector3<Scalar> Sqrt(const _Vector3<Scalar> &a)  { return _Vector3<Scalar>(std::sqrt(a.x),  std::sqrt(a.y),  std::sqrt(a.z));  }
template <class Scalar> inline const _Vector3<Scalar> operator*(Scalar scale, const _Vector3<Scalar> &a) { return a * scale; }
template <class Scalar> inline const Scalar  Dot(const _Vector3<Scalar> &a, const _Vector3<Scalar> &b) { return a.x*b.x+a.y*b.y+a.z*b.z; }
template <class Scalar> inline const _Vector3<Scalar> Cross(const _Vector3<Scalar> &a, const _Vector3<Scalar> &b) {
    return _Vector3<Scalar>(
        a.y*b.z-a.z*b.y,
        a.z*b.x-a.x*b.z,
        a.x*b.y-a.y*b.x
    );
}
// stream
template <class Scalar, class ostream> inline ostream &operator<<(ostream &out, const _Vector3<Scalar> &a) {
    out << "vec3<" << typeid(Scalar).name() << ">: [" << a.x << ", " << a.y << ", " << a.z << "]";
    return out;
}

typedef _Vector3<Float>    Float3;
typedef _Vector3<int32_t>  Int3;
typedef _Vector3<uint32_t> UInt3;

}
