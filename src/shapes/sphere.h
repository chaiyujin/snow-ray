#pragma once
#include <core/shape.h>

namespace snowrt {

class Sphere: public Shape {
    Float3 mCenter;
    Float  mRadius;

public:
    Sphere(Float3 center, Float radius): mCenter(center), mRadius(radius) {}
    Sphere(const Sphere& b): mCenter(b.mCenter), mRadius(b.mRadius) {}
    ~Sphere() {}

    bool intersect(const Ray& ray) const;
    bool intersect(const Ray& ray, Float *tHitPtr, SurfaceInteraction *insectPtr) const;
};

}