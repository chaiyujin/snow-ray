#pragma once
#include "sphere.h"

namespace snowrt {

bool Sphere::intersect(const Ray& ray) const {
    return true;
}

bool Sphere::intersect(const Ray& ray, Float *tHitPtr, SurfaceInteraction *insectPtr) const {
    Float phi;
    Float3 pHit;
    /* discriminant */
    Float3 oc = ray.origin() - mCenter;
    Float a = Dot(ray.direction(), ray.direction());
    Float b = Dot(ray.direction(), oc);
    Float c = Dot(oc, oc) - mRadius*mRadius;
    Float disc = b*b - a*c;
    if (disc <= 0) return false;
    Float tmp = (-b - std::sqrt(disc))/a;
    if (tmp > 1e-5 && tmp < *tHitPtr)
        *tHitPtr = tmp;
    tmp = (-b + std::sqrt(disc))/a;
    if (tmp > 1e-5 && tmp < *tHitPtr)
        *tHitPtr = tmp;
    insectPtr->time = *tHitPtr;
    insectPtr->point = ray(tmp);
    insectPtr->normal = (insectPtr->point - mCenter).normalized();
    return true;
}


}