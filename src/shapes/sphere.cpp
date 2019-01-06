#include "sphere.h"

namespace snowrt {

bool Sphere::intersect(const Ray& ray) const {Float phi;
    Float3 pHit;
    /* discriminant */
    Float3 oc = ray.origin() - mCenter;
    Float a = Dot(ray.direction(), ray.direction());
    Float b = Dot(ray.direction(), oc);
    Float c = Dot(oc, oc) - mRadius*mRadius;
    Float disc = b*b - a*c;
    if (disc <= 0) return false;
    return true;
}

bool Sphere::intersect(const Ray& ray, Float *tHitPtr, SurfaceInteraction *insectPtr) const {
    auto setInsect = [&]() -> void {
        insectPtr->time = *tHitPtr;
        insectPtr->point = ray(*tHitPtr);
        insectPtr->normal = (insectPtr->point - mCenter).normalized();
        insectPtr->wo = -ray.direction();
        insectPtr->time = *tHitPtr;
        insectPtr->shape = this;
        if (Dot(insectPtr->normal, insectPtr->wo) < 0)
            insectPtr->normal = -insectPtr->normal;
    };

    Float phi;
    Float3 pHit;
    /* discriminant */
    Float3 oc = ray.origin() - mCenter;
    Float a = Dot(ray.direction(), ray.direction());
    Float b = Dot(ray.direction(), oc);
    Float c = Dot(oc, oc) - mRadius*mRadius;
    Float disc = b*b - a*c;
    if (disc > 0) {
        Float tmp = (-b - std::sqrt(disc))/a;
        if (tmp > 0.1 && tmp < *tHitPtr) {
            *tHitPtr = tmp;
            setInsect();
            return true;
        }
        tmp = (-b + std::sqrt(disc))/a;
        if (tmp > 0.1 && tmp < *tHitPtr) {
            *tHitPtr = tmp;
            setInsect();
            return true;
        }
    }
    return false;
}


}