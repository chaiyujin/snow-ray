#pragma once
#include "vec.h"
#include "log.h"

/* ===================
   _AABB2 Declaration
   =================== */
namespace snowrt {
/** ccw rotation
 * y
 * ^
 * |
 * 
 * 3---------2
 * |         |
 * |         |
 * |         |
 * 0---------1  -> x
 * */
template <class Scalar>
struct _AABB2 {
    _Vector2<Scalar> min;
    _Vector2<Scalar> max;

    inline _AABB2();
    inline _AABB2(const _AABB2& b);
    inline _AABB2(const _Vector2<Scalar>& minPt, const _Vector2<Scalar>& maxPt);
    inline explicit _AABB2(const _Vector2<Scalar>& minPt);

    inline const _Vector2<Scalar> corner(uint32_t index) const;
    inline const _Vector2<Scalar> diagonal() const;

    inline const _AABB2  operator+ (const _Vector2<Scalar>& p) const;
    inline const _AABB2  operator& (const _AABB2<Scalar>&   b) const;
    inline const _AABB2  operator| (const _AABB2<Scalar>&   b) const;
    inline       _AABB2& operator+=(const _Vector2<Scalar>& p);
    inline       _AABB2& operator&=(const _AABB2<Scalar>&   b);
    inline       _AABB2& operator|=(const _AABB2<Scalar>&   b);

    template <class U>
    inline       _AABB2& expand(U delta);
    template <class U>
    inline const _AABB2  expanded(U delta) const;

    inline uint32_t maxExtent() const;
    inline _Vector2<Scalar> lerp(const _Vector2<Float>& t) const;
    inline _Vector2<Float>  offset(const _Vector2<Scalar>& p) const;
};
template <class Scalar> bool Overlaps(const _AABB2<Scalar>& a, const _AABB2<Scalar>& b);
template <class Scalar> bool Inside(const _Vector2<Scalar>& p, const _AABB2<Scalar>& b, bool excludeMax=false);
template <class Scalar, class ostream> ostream &operator<<(ostream &out, const _AABB2<Scalar> &box);
}

/* ===================
   _AABB2 Definition
   =================== */
namespace snowrt {

template <class Scalar> inline _AABB2<Scalar>::_AABB2() {
    Scalar _min = std::numeric_limits<Scalar>::lowest();
    Scalar _max = std::numeric_limits<Scalar>::max();
    min.x = min.y = _max;
    max.x = max.y = _min;
}
template <class Scalar> inline _AABB2<Scalar>::_AABB2(const _AABB2<Scalar>& b)
    : min(b.min), max(b.max) {}
template <class Scalar> inline _AABB2<Scalar>::_AABB2(const _Vector2<Scalar>& minPt, const _Vector2<Scalar>& maxPt)
    : min(minPt), max(maxPt) {}
template <class Scalar> inline _AABB2<Scalar>::_AABB2(const _Vector2<Scalar>& minPt)
    : min(minPt), max(minPt) {}

template <class Scalar> inline const _Vector2<Scalar> _AABB2<Scalar>::corner(uint32_t index) const {
    log::assertion(index>=0&&index<=3, "AABB2 corner index {} is out of range [0, 4)", index);
    return _Vector2<Scalar>(
        (index==0||index==3)?min.x:max.x,
        (index==0||index==1)?min.y:max.y
    );
}
template <class Scalar> inline const _Vector2<Scalar> _AABB2<Scalar>::diagonal() const {
    return max - min;
}
template <class Scalar> inline const _AABB2<Scalar> _AABB2<Scalar>::operator+ (const _Vector2<Scalar>& p) const {
    return _AABB2<Scalar>(
        _Vector2<Scalar>(std::min(min.x, p.x), std::min(min.y, p.y)),
        _Vector2<Scalar>(std::max(max.x, p.x), std::max(max.y, p.y))
    );
}
template <class Scalar> inline const _AABB2<Scalar> _AABB2<Scalar>::operator& (const _AABB2<Scalar>&   b) const {
    return _AABB2<Scalar>(
        _Vector2<Scalar>(std::max(min.x, b.min.x), std::max(min.y, b.min.y)),
        _Vector2<Scalar>(std::min(max.x, b.max.x), std::min(max.y, b.max.y))
    );
}
template <class Scalar> inline const _AABB2<Scalar> _AABB2<Scalar>::operator| (const _AABB2<Scalar>&   b) const {
    return _AABB2<Scalar>(
        _Vector2<Scalar>(std::min(min.x, b.min.x), std::min(min.y, b.min.y)),
        _Vector2<Scalar>(std::max(max.x, b.max.x), std::max(max.y, b.max.y))
    );
}
template <class Scalar> inline _AABB2<Scalar>& _AABB2<Scalar>::operator+=(const _Vector2<Scalar>& p) {
    min.x = std::min(min.x, p.x); min.y = std::min(min.y, p.y);
    max.x = std::max(max.x, p.x); max.y = std::max(max.y, p.y);
    return *this;
}
template <class Scalar> inline _AABB2<Scalar>& _AABB2<Scalar>::operator&=(const _AABB2<Scalar>&   b) {
    min.x = std::max(min.x, b.min.x); min.y = std::max(min.y, b.min.y);
    max.x = std::min(max.x, b.max.x); max.y = std::min(max.y, b.max.y);
    return *this;
}
template <class Scalar> inline _AABB2<Scalar>& _AABB2<Scalar>::operator|=(const _AABB2<Scalar>&   b) {
    min.x = std::min(min.x, b.min.x); min.y = std::min(min.y, b.min.y);
    max.x = std::max(max.x, b.max.x); max.y = std::max(max.y, b.max.y);
    return *this;
}

template <class Scalar> inline uint32_t _AABB2<Scalar>::maxExtent() const {
    auto d = this->diagonal();
    if (d.x > d.y) return 0; else return 1;
}
template <class Scalar> inline _Vector2<Scalar> _AABB2<Scalar>::lerp(const _Vector2<Float>& t) const {
    return _Vector2<Scalar>(
        Lerp(t.x, min.x, max.x),
        Lerp(t.y, min.y, max.y)
    );
}
template <class Scalar> inline _Vector2<Float> _AABB2<Scalar>::offset(const _Vector2<Scalar>& p) const {
    _Vector2<Float> delta(p.x-min.x, p.y-min.y);
    _Vector2<Float> diag(max.x-min.x, max.y-min.y);
    if (diag.x > 0) delta.x /= diag.x;
    if (diag.y > 0) delta.y /= diag.y;
    return diag;
}
template <class Scalar> template<class U> inline _AABB2<Scalar>& _AABB2<Scalar>::expand(U delta) {
    min.x -= delta; min.y -= delta;
    max.x += delta; max.y += delta;
    return *this;
}
template <class Scalar> template<class U> inline const _AABB2<Scalar> _AABB2<Scalar>::expanded(U delta) const {
    return _AABB2<Scalar>(
        _Vector2<Scalar>(min.x - delta, min.y - delta),
        _Vector2<Scalar>(max.x + delta, max.y + delta)
    );
}

// static 

template <class Scalar> inline bool Overlaps(const _AABB2<Scalar>& a, const _AABB2<Scalar>& b) {
    bool x = (a.max.x >= b.min.x) && (a.min.x <= b.max.x);
    bool y = (a.max.y >= b.min.y) && (a.min.y <= b.max.y);
    return x && y;
}
template <class Scalar> inline bool Inside(const _Vector2<Scalar>& p, const _AABB2<Scalar>& b, bool excludeMax) {
    if (excludeMax)
        return p.x >= b.min.x && p.x < b.max.x &&
               p.y >= b.min.y && p.y < b.max.y;
    else
        return p.x >= b.min.x && p.x <= b.max.x &&
               p.y >= b.min.y && p.y <= b.max.y;
}
template <class Scalar, class ostream> ostream &operator<<(ostream &out, const _AABB2<Scalar> &box) {
    out << "axis-box2<" << typeid(Scalar).name() << ">: ["
        << box.min.x << ", " << box.min.y << "] ~ ["
        << box.max.x << ", " << box.max.y << "]";
    return out;
}

typedef _AABB2<Float>   AABB2f;
typedef _AABB2<int32_t> AABB2i;

}

namespace snowrt {
/**
 *          y
 *          ^
 *          |   
 *       
 *          3---------2
 *         /|        /|
 *        / |       / |
 *       7--+------6  |
 *       |  0------+--1   -> x
 *       | /       | /
 *       |/        |/
 *       4---------5
 * 
 *     / 
 *    v
 *   z
 * 
 * */
template <class Scalar>
struct _AABB3 {
    _Vector3<Scalar> min;
    _Vector3<Scalar> max;

    inline _AABB3();
    inline _AABB3(const _AABB3<Scalar>& b);
    inline _AABB3(const _Vector3<Scalar>& minPt, const _Vector3<Scalar>& maxPt);
    inline explicit _AABB3(const _Vector3<Scalar>& minPt);

    inline const _Vector3<Scalar> corner(uint32_t index) const;
    inline const _Vector3<Scalar> diagonal() const;

    inline const _AABB3  operator+ (const _Vector3<Scalar>& p) const;
    inline const _AABB3  operator& (const _AABB3<Scalar>&   b) const;
    inline const _AABB3  operator| (const _AABB3<Scalar>&   b) const;
    inline       _AABB3& operator+=(const _Vector3<Scalar>& p);
    inline       _AABB3& operator&=(const _AABB3<Scalar>&   b);
    inline       _AABB3& operator|=(const _AABB3<Scalar>&   b);

    template <class U>
    inline       _AABB3& expand(U delta);
    template <class U>
    inline const _AABB3  expanded(U delta) const;

    inline uint32_t maxExtent() const;
    inline _Vector3<Scalar> lerp(const _Vector3<Float>& t) const;
    inline _Vector3<Float>  offset(const _Vector3<Scalar>& p) const;
};
template <class Scalar> bool Overlaps(const _AABB3<Scalar>& a, const _AABB3<Scalar>& b);
template <class Scalar> bool Inside(const _Vector3<Scalar>& p, const _AABB3<Scalar>& b, bool excludeMax=false);
template <class Scalar, class ostream> ostream &operator<<(ostream &out, const _AABB3<Scalar> &box);
}

namespace snowrt {

template <class Scalar> inline _AABB3<Scalar>::_AABB3() {
    Scalar _min = std::numeric_limits<Scalar>::lowest();
    Scalar _max = std::numeric_limits<Scalar>::max();
    min.x = min.y = min.z = _max;
    max.x = max.y = max.z = _min;
}
template <class Scalar> inline _AABB3<Scalar>::_AABB3(const _AABB3<Scalar>& b): min(b.min), max(b.max) {}
template <class Scalar> inline _AABB3<Scalar>::_AABB3(const _Vector3<Scalar>& minPt, const _Vector3<Scalar>& maxPt): min(minPt), max(maxPt) {}
template <class Scalar> inline _AABB3<Scalar>::_AABB3(const _Vector3<Scalar>& minPt): min(minPt), max(minPt) {}

template <class Scalar> inline const _Vector3<Scalar> _AABB3<Scalar>::diagonal() const { return max - min; }
template <class Scalar> inline const _Vector3<Scalar> _AABB3<Scalar>::corner(uint32_t index) const {
    return _Vector3<Scalar>(
        (index==0||index==3||index==4||index==7)?min.x:max.x,
        (index==0||index==1||index==4||index==5)?min.y:max.y,
        (index<=3)?min.z:max.z
    );
}

template <class Scalar> inline const _AABB3<Scalar>  _AABB3<Scalar>::operator+ (const _Vector3<Scalar>& p) const {
    return _AABB3<Scalar>(
        _Vector3<Scalar>(std::min(min.x, p.x), std::min(min.y, p.y), std::min(min.z, p.z)),
        _Vector3<Scalar>(std::max(max.x, p.x), std::max(max.y, p.y), std::max(max.z, p.z))
    );
}
template <class Scalar> inline const _AABB3<Scalar>  _AABB3<Scalar>::operator& (const _AABB3<Scalar>&   b) const {
    return _AABB3<Scalar>(
        _Vector3<Scalar>(std::max(min.x, b.min.x), std::max(min.y, b.min.y), std::max(min.z, b.min.z)),
        _Vector3<Scalar>(std::min(max.x, b.max.x), std::min(max.y, b.max.y), std::min(max.z, b.max.z))
    );
}
template <class Scalar> inline const _AABB3<Scalar>  _AABB3<Scalar>::operator| (const _AABB3<Scalar>&   b) const {
    return _AABB3<Scalar>(
        _Vector3<Scalar>(std::min(min.x, b.min.x), std::min(min.y, b.min.y), std::min(min.z, b.min.z)),
        _Vector3<Scalar>(std::max(max.x, b.max.x), std::max(max.y, b.max.y), std::max(max.z, b.max.z))
    );
}
template <class Scalar> inline _AABB3<Scalar>& _AABB3<Scalar>::operator+=(const _Vector3<Scalar>& p) {
    min.x = std::min(min.x, p.x); min.y = std::min(min.y, p.y); min.z = std::min(min.z, p.z);
    max.x = std::max(max.x, p.x); max.y = std::max(max.y, p.y); max.z = std::max(max.z, p.z);
    return *this;
}
template <class Scalar> inline _AABB3<Scalar>& _AABB3<Scalar>::operator&=(const _AABB3<Scalar>&   b) {
    min.x = std::max(min.x, b.min.x); min.y = std::max(min.y, b.min.y); min.z = std::max(min.z, b.min.z);
    max.x = std::min(max.x, b.max.x); max.y = std::min(max.y, b.max.y); max.z = std::min(max.z, b.max.z);
    return *this;
}
template <class Scalar> inline _AABB3<Scalar>& _AABB3<Scalar>::operator|=(const _AABB3<Scalar>&   b) {
    min.x = std::min(min.x, b.min.x); min.y = std::min(min.y, b.min.y); min.z = std::min(min.z, b.min.z);
    max.x = std::max(max.x, b.max.x); max.y = std::max(max.y, b.max.y); max.z = std::max(max.z, b.max.z);
    return *this;
}

template <class Scalar> inline uint32_t _AABB3<Scalar>::maxExtent() const {
    auto d = this->diagonal();
    if (d.x > d.y && d.x > d.z) return 0;
    else if (d.y > d.z)         return 1;
    else                        return 2;
}
template <class Scalar> inline _Vector3<Scalar> _AABB3<Scalar>::lerp(const _Vector3<Float>& t) const {
    return _Vector3<Scalar>(
        Lerp(t.x, min.x, max.x),
        Lerp(t.y, min.y, max.y),
        Lerp(t.z, min.z, max.z)
    );
}
template <class Scalar> inline _Vector3<Float>  _AABB3<Scalar>::offset(const _Vector3<Scalar>& p) const {
    _Vector3<Float> delta(p.x-min.x, p.y-min.y, p.z-min.z);
    _Vector3<Float> diag(max.x-min.x, max.y-min.y, max.z-min.z);
    if (diag.x > 0) delta.x /= diag.x;
    if (diag.y > 0) delta.y /= diag.y;
    if (diag.z > 0) delta.z /= diag.z;
    return diag;
}
template <class Scalar> template <class U> inline _AABB3<Scalar>& _AABB3<Scalar>::expand(U delta) {
    min.x -= delta; min.y -= delta; min.z -= delta;
    max.x += delta; max.y += delta; max.z += delta;
    return *this;
}
template <class Scalar> template <class U> inline const _AABB3<Scalar> _AABB3<Scalar>::expanded(U delta) const {
    return _AABB3<Scalar>(
        _Vector3<Scalar>(min.x - delta, min.y - delta, min.z - delta),
        _Vector3<Scalar>(max.x + delta, max.y + delta, max.z + delta)
    );
}

// static

template <class Scalar> bool Overlaps(const _AABB3<Scalar>& a, const _AABB3<Scalar>& b) {
    bool x = (a.max.x >= b.min.x) && (a.min.x <= b.max.x);
    bool y = (a.max.y >= b.min.y) && (a.min.y <= b.max.y);
    bool z = (a.max.z >= b.min.z) && (a.min.z <= b.max.z);
    return x && y && z;
}
template <class Scalar> bool Inside(const _Vector3<Scalar>& p, const _AABB3<Scalar>& b, bool excludeMax) {
    if (excludeMax)
        return p.x >= b.min.x && p.x < b.max.x &&
               p.y >= b.min.y && p.y < b.max.y &&
               p.z >= b.min.z && p.z < b.max.z;
    else
        return p.x >= b.min.x && p.x <= b.max.x &&
               p.y >= b.min.y && p.y <= b.max.y &&
               p.z >= b.min.z && p.z <= b.max.z;
}
template <class Scalar, class ostream> ostream &operator<<(ostream &out, const _AABB3<Scalar> &box) {
    out << "axis-box3<" << typeid(Scalar).name() << ">: ["
        << box.min.x << ", " << box.min.y << ", " << box.min.z << "] ~ ["
        << box.max.x << ", " << box.max.y << ", " << box.max.z << "]";
    return out;
}

typedef _AABB3<Float>   AABB3f;
typedef _AABB3<int32_t> AABB3i;

}