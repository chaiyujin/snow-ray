#pragma once
#include "../utils/utils.h"
#include "ray.h"
#include "intersect.h"

namespace snowrt {

class Material {
    Float3 mEmission;
    Float3 mAlbedo;
public:
    Material(const Float3 &emission, const Float3 &albedo)
        : mEmission(emission), mAlbedo(albedo) {}
    virtual void scatter(const SurfaceInteraction *si, Ray &rayIn) const = 0;
    const Float3 &albedo() const { return mAlbedo; }
    const Float3 &emission() const { return mEmission; }
};

class IdeaDiffuse : public Material {
public:
    IdeaDiffuse(const Float3 &emission, const Float3 &albedo)
        : Material(emission, albedo) {}
    virtual void scatter(const SurfaceInteraction *si, Ray &rayIn) const {
        auto n = si->normal;
        if (Dot(n, si->wo) < 0) n = -n;
        auto wi = random::InHemiShpere(n);
        rayIn.setOrigin(si->point + n * si->shadowBias);
        rayIn.setDirection(wi);
    }
};

class IdeaSpecular : public Material {
public:
    IdeaSpecular(const Float3 &emission, const Float3 &albedo)
        : Material(emission, albedo) {}
    virtual void scatter(const SurfaceInteraction *si, Ray &rayIn) const {
        auto n = si->normal;
        if (Dot(n, si->wo) < 0) n = -n;
        auto wi = -Reflect(si->wo, n).normalized();
        rayIn.setOrigin(si->point + n * si->shadowBias);
        rayIn.setDirection(wi);
    }
};

class IdeaRefraction : public Material {
public:
    IdeaRefraction(const Float3 &emission, const Float3 &albedo)
        : Material(emission, albedo) {}
    virtual void scatter(const SurfaceInteraction *si, Ray &rayIn) const {
        auto wi = -Reflect(si->wo, si->normal).normalized();
        rayIn.setOrigin(si->point);
        rayIn.setDirection(wi);
    }
};

}