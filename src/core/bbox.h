#pragma once
#include "vec.h"
#include "log.h"

/* ===================
   _AABB2 Declaration
   =================== */
namespace snowray {
/** ccw rotation
 * 3---------2
 * |         |
 * |         |
 * |         |
 * 0---------1
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
namespace snowray {

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
}
template <class Scalar> inline _AABB2<Scalar>& _AABB2<Scalar>::operator&=(const _AABB2<Scalar>&   b) {
    min.x = std::max(min.x, b.min.x); min.y = std::max(min.y, b.min.y);
    max.x = std::min(max.x, b.max.x); max.y = std::min(max.y, b.max.y);
}
template <class Scalar> inline _AABB2<Scalar>& _AABB2<Scalar>::operator|=(const _AABB2<Scalar>&   b) {
    min.x = std::min(min.x, b.min.x); min.y = std::min(min.y, b.min.y);
    max.x = std::max(max.x, b.max.x); max.y = std::max(max.y, b.max.y);
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
}
template <class Scalar> template<class U> inline const _AABB2<Scalar> _AABB2<Scalar>::expanded(U delta) const {
    return _AABB2<Scalar>(
        _Vector2<Scalar>(min.x - delta, min.y - delta),
        _Vector2<Scalar>(max.x + delta, max.y + delta)
    );
}


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