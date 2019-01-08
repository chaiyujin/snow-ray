#pragma once
#include "../utils/utils.h"
#include "spectrum.h"

namespace snowrt {

enum BSDFType {
    Undefined    = 0,
    Reflection   = 1 << 0,
    Transmission = 1 << 1,
    Diffuse      = 1 << 2,
    Specular     = 1 << 3,
    Glossy       = 1 << 4,
    All          = Reflection | Transmission | Diffuse |
                   Specular   | Glossy
};

class BSDF {
public:
    const BSDFType type;

    bool matchFlags(BSDFType flag) const { return (type & flag) == type; }
    virtual Spectrum f(const Float3 &wo, const Float3 &wi) const = 0;
    virtual Spectrum sampleF(const Float3 &wo, Float3 *wi,
       const Float2 &sample, Float *pdf,
       BSDFType *sampledType = nullptr) const;
};

class BSDFs {

};

}