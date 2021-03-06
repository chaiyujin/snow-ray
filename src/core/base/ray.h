#pragma once
#include "../utils/utils.h"

namespace snowrt {

class Ray {
    Float3 mPos;
    Float3 mDir;
    Float  mTime;
    Float  mTimeMax;
    Float  mProb;
public:
    Ray() : mTime(0.f), mTimeMax(constants::Infinity), mProb(1.0) {}
    Ray(const Float3& pos, const Float3& dir, Float time=0.f, Float timeMax=constants::Infinity)
        : mPos(pos), mDir(dir), mTime(time), mTimeMax(timeMax), mProb(1.0) {}
    Ray(const Ray& b): mPos(b.mPos), mDir(b.mDir), mTime(b.mTime)
                     , mTimeMax(b.mTimeMax), mProb(b.mProb) {}
    virtual ~Ray() {}
    
    Float3 operator()(Float t) const { return mPos + mDir * t; }
    const Float3 &origin() const { return mPos; }
    const Float3 &direction() const { return mDir; }
    void setOrigin(const Float3 &o) { mPos = o; }
    void setDirection(const Float3 &d) { mDir = d; }
    void setProb(Float prob) { mProb = prob; }
    Float prob() const { return mProb; }
};

template <class ostream> inline ostream& operator<<(ostream &out, const Ray &ray) {
    out << "o: " << ray.origin() << ", d: " << ray.direction();
    return out;
}

inline Float3 Reflect(const Float3 &wo, const Float3 &normal) {
    return wo - normal*2*Dot(wo, normal);
}

}