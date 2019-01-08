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
    Float mEta;
public:
    IdeaRefraction(const Float3 &emission, const Float3 &albedo, Float eta)
        : Material(emission, albedo)
        , mEta(eta) {}
    virtual void scatter(const SurfaceInteraction *si, Ray &rayIn) const {
        auto n = si->normal.normalized();
        auto i = -si->wo.normalized();
        bool into = true;
        if (Dot(n, si->wo) < 0) { n = -n; into = false; }
        /* k */
        Float theta1 = Dot(-i, n);
        Float theta2 = 0;
        Float eta = (into)? (1/mEta) : mEta;
        Float k = 1 - eta * eta * (1 - theta1 * theta1);
        Float F = 1.0;
        Float3 t;
        if (k >= 0) {
            t = i * eta - n * (eta * theta1 + std::sqrt(k));
            t.normalize();
            theta2 = Dot(-n, t);
            {
                Float r0 = (1-mEta)/(1+mEta); r0 = r0 * r0;
                Float c = 1 - (into ? theta1 : theta2);
                Float cc = c*c;
                F = r0 + (1-r0)*cc*cc*c;
            }
        }
        if (random::uniform() < F) {
            // reflection
            auto wi = -Reflect(si->wo, si->normal).normalized();
            rayIn.setOrigin(si->point + n * si->shadowBias);
            rayIn.setDirection(wi);
            rayIn.setProb(F);
        } else {
            // transmit
            rayIn.setOrigin(si->point + n * si->shadowBias);
            rayIn.setDirection(t);
            rayIn.setProb(1-F);
        }
    }
};

}