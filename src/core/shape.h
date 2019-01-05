#pragma once
#include "ray.h"
#include "intersect.h"

namespace snowrt {

class Shape {

public:
    Shape() {}
    Shape(const Shape& b) {}
    virtual ~Shape();

    virtual bool intersect(const Ray& ray) const = 0;
    virtual bool intersect(const Ray& ray, Float *tHitPtr, SurfaceInteraction *insectPtr) const = 0;
};

}