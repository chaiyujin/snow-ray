#pragma once
#include "vec.h"

namespace snowray {

class Ray {
    Float3 mPos;
    Float3 mDir;
    Float  mTime;
    Float  mTimeMax;
public:
    Ray() : mTime(0.f), mTimeMax(constants::Infinity) {}
    Ray(const Float3& pos, const Float3& dir, Float time=0.f,
        Float timeMax=constants::Infinity) : mPos(pos), mDir(dir), mTime(time), mTimeMax(timeMax) {}
    
    Float3 operator()(Float t) const { return mPos + mDir * t; }
};

}