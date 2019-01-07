#pragma once
#include <core/core.h>

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

    AABB3f getBounds() const { return AABB3f(mCenter).expanded(mRadius); }
    bool intersect(const Ray &ray) const;
    bool intersect(Interaction *insectPtr, const Ray &ray, Float tMin=0, Float tMax=constants::MaxFloat) const;
    const Material *materialPtr() const { return mMaterialPtr; }
};

}