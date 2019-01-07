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
        auto wi = random::InHemiShpere(si->normal);
        rayIn.setOrigin(si->point);
        rayIn.setDirection(wi.normalized());
    }
};

class IdeaSpecular : public Material {
public:
    IdeaSpecular(const Float3 &emission, const Float3 &albedo)
        : Material(emission, albedo) {}
    virtual void scatter(const SurfaceInteraction *si, Ray &rayIn) const {
        rayIn.setOrigin(si->point);
        rayIn.setDirection(-Reflect(si->wo, si->normal).normalized());
    }
};

}