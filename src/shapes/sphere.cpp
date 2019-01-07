#include "sphere.h"

namespace snowrt {

bool Sphere::intersect(const Ray &ray) const {
    Float phi;
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

bool Sphere::intersect(Interaction *insPtr, const Ray &ray, Float tMin, Float tMax) const {
    /* discriminant */
    Float3 oc = ray.origin() - mCenter;
    Float a = Dot(ray.direction(), ray.direction());
    Float b = Dot(ray.direction(), oc)*2;
    Float c = Dot(oc, oc) - mRadius*mRadius;
    Float t0, t1;
    if (!Quadratic(a, b, c, &t0, &t1))
        return false;
    if (t1 <= tMin || t0 >= tMax)
        return false;
    Float t = t0;
    if (t <= tMin) {
        t = t1;
        if (t >= tMax)
            return false;
    }
    /* set interaction record */ {
        auto pt = ray(t);
        auto n = (pt - mCenter).normalized();
        if (Dot(n, -ray.direction()) < 0) n = -n;
        auto *insectPtr = (SurfaceInteraction *)insPtr;
        insectPtr->time = t;
        insectPtr->normal = n;
        insectPtr->point = pt + n * options::DynamicShadowEps(mRadius);
        insectPtr->wo = -ray.direction();
        insectPtr->time = t;
        insectPtr->shape = this;
    }
    return true;
}


}