#pragma once
#include <core/log.h>
#include <core/shape.h>
#include <core/efloat.h>
#include <core/material.h>

namespace snowrt {

class Sphere: public Shape {
    Float3   mCenter;
    Float    mRadius;
    const Material *mMaterialPtr;
public:
    Sphere(Float3 center, Float radius, const Material * material)
        : mCenter(center), mRadius(radius), mMaterialPtr(material) {}
    Sphere(const Sphere& b): mCenter(b.mCenter), mRadius(b.mRadius), mMaterialPtr(b.mMaterialPtr) {}
    ~Sphere() {}

    bool intersect(const Ray& ray) const;
    bool intersect(const Ray& ray, Float *tHitPtr, SurfaceInteraction *insectPtr) const;
    const Material *materialPtr() const { return mMaterialPtr; }
};

}