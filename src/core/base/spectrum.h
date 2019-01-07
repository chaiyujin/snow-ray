#pragma once
#include "../utils/utils.h"

namespace snowrt {

typedef _Vector3<uint8_t> RGB;

class ISpectrum {
public:
    virtual RGB toRGB() const = 0;
};

class RGBSpectrum {
    Float3 mRGB3f;
public:
    RGBSpectrum() : mRGB3f(0,0,0) {}
    RGBSpectrum(const Float3 &rgb) : mRGB3f(rgb) {}
    RGBSpectrum(const RGBSpectrum &b) : mRGB3f(b.mRGB3f) {}
    RGBSpectrum operator+(const RGBSpectrum &b) const {
        return RGBSpectrum(mRGB3f + b.mRGB3f);
    }
    RGBSpectrum &operator+=(const RGBSpectrum &b) {
        mRGB3f += b.mRGB3f;
        return *this;
    }
    RGB toRGB() {
        auto toByte = [](Float v) -> uint8_t {
            return (uint8_t)(pow(Clamp(v,0.f,1.f),1/2.2)*255);
        };
        return RGB(
            toByte(mRGB3f.x),
            toByte(mRGB3f.y),
            toByte(mRGB3f.z)
        );
    }
};

typedef RGBSpectrum Spectrum;

}