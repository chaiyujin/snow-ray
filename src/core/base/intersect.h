#pragma once
#include "../utils/utils.h"
#include "bbox.h"

namespace snowrt {

/* struct of interaction */

struct Interaction {
    Float3 point;
    Float3 normal;
    Float3 pError;
    Float3 wo;
    Float  time;

    Interaction() {}
    Interaction(const Float3 &p, const Float3 &n, const Float3 &err,
                const Float3 &wo, Float time)
        : point(p), normal(n), pError(err), wo(wo), time(time) {}
    virtual ~Interaction() {}

};

struct SurfaceInteraction : public Interaction {
    Float2 uv;
    Float3 dpdu, dpdv;
    Float3 dndu, dndv;
    const Shape *shape;
    
    SurfaceInteraction() : shape(nullptr) {}
    SurfaceInteraction(const Float3 &p, const Float3 &err,
                       const Float2 &uv, const Float3 &wo,
                       const Float3 &dpdu, const Float3 &dpdv,
                       const Float3 &dndu, const Float3 &dndv,
                       Float time, const Shape* shape)
        : Interaction(p, Cross(dpdu, dpdv).normalized(), err, wo, time)
        , uv(uv), dpdu(dpdu), dpdv(dpdv), dndu(dndu), dndv(dndv)
        , shape(shape) {}
};

/* interface of hitable */
class IHitable {
public:
    /* get world bounding box */
    virtual AABB3f getBounds() const = 0;
    virtual bool intersect(const Ray &ray) const = 0;
    virtual bool intersect(Interaction *insectPtr, const Ray &ray, Float tMin=0, Float tMax=constants::MaxFloat) const = 0;
};

}